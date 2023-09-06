import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.*;
import javax.swing.border.Border;
import java.util.Random;
import java.lang.Math.*;
import java.util.ArrayList;
public class GameBoard extends JFrame implements ActionListener {
	
    private JPanel topPanel;
    private JPanel leftPanel;
    private JPanel rightPanel;
    private JPanel bottomPanel;
    private JPanel gameBoard;
    private GameSpace [][] gameSpaces;
    private int numPlayers, rows, columns, highlightHeight;
    private Color setupColor; //used to set the color of the piece that starts in each space at the beginning of the game
    private Color defaultButtonColor; //used when button is selected/deselected
    private JButton quit, colorBlindButton, rules, reserve, newGame;

    private JLabel colorBlindInfo, currentTurn, reserveInfo, colorKey, declareWinner, turnTracker, playerInfo, ruleText;

    private GameSpace moveFrom; //space that has been selected to move from
    private GameSpace moveTo; //space that has been selected to move to
    
    private boolean moveFromSelected; //true when a space has already been selected to move from, used to determine if a space has been selected to move from or move to
    private int turn; //current turn, 0 to 3
    private boolean colorBlindOn;
    private Player currentPlayer;
    private Player[] players;
    private int noMoveCount; //Counts how many players in a row cannot move. If 3 players cannot move the 4th player wins.
    private boolean gameWon; //stops moves from being made if the game has ended
    private MoveHandler moveHandler;
    private int player1num, player2num, player3num, player4num;
    private String thirdLastTurn;
    private String secondLastTurn;
    private String lastTurn;
    private boolean lastMoveWasReserve;
    private GameBoard game;
    
    
    //true when a space has already been selected to move from, used to determine if a space has been selected to move from or move to
     
    public GameBoard(int player1num, int player2num, int player3num, int player4num) {
    	
    	rows = 8;
    	columns = 8;
    	moveFromSelected = false;
    	Random rand = new Random();
    	colorBlindOn = false;
    	noMoveCount = 0;
    	gameWon = false;
    	moveHandler = new MoveHandler();
    	this.player1num = player1num;
    	this.player2num = player2num;
    	this.player3num = player3num;
    	this.player4num = player4num;
    	thirdLastTurn = " ";
    	secondLastTurn = " ";
    	lastTurn = " ";
    	lastMoveWasReserve = false;

    	turn = rand.nextInt(4);
    	players = new Player[4];

    	players[0] = new Player(player1num, Color.red);
    	players[1] = new Player(player2num, Color.green);
    	players[2] = new Player(player3num, Color.cyan);
    	players[3] = new Player(player4num, Color.yellow);

    	currentPlayer = players[turn];


    	topPanel = new JPanel();
    	rightPanel = new JPanel();
    	leftPanel = new JPanel();
    	gameBoard = new JPanel();
    	declareWinner = new JLabel(" ");
		topPanel.add(declareWinner);
    	colorBlindInfo = new JLabel(" ");
		topPanel.add(colorBlindInfo);
    	quit = new JButton("Quit");
    	colorBlindButton = new JButton("Toggle Color Defiency Settings");
    	colorBlindButton.addActionListener(this);
    	quit.addActionListener(this);
    	rules = new JButton("Rules");
    	rules.addActionListener(e -> { rules();} );
		ruleText = new JLabel("<html>-This game deals with stacks of pieces. A single piece can be considered a stack of height 1.<br>-Stacks may be moved horizontally or vertically, but not diagonally.<br>-A player may only move a stack if the top piece of the stack is of their color.<br>-A stack may be moved up to h spaces, h being the height of the stack. A stack may only be moved in one direction per move, for example, 2 spaces up is permitted but 1 up and 1 left is not.<br>-When a stack is moved x spaces, only the top x pieces of the stack move, for example, if a 5 high stack is moved 3 spaces, the top 3 pieces of the stack move and the other 2 pieces are left behind.<br>-If a player's move causes a stack to grow to a height of more than 5 pieces, then pieces will be removed from the bottom of the stack until the stack has a height of 5. Any removed pieces which are of the player's color are kept as reserve pieces, all other removed pieces are deleted from the game.<br>-Reserve pieces may be placed anywhere on the board.<br>-If a player has no possible moves, their turn is skipped. When only 1 player can move, that player wins.</html>");
    	reserve = new JButton("Reserve");
    	defaultButtonColor = reserve.getBackground();
    	reserve.addActionListener(this);
    	
    	currentTurn = new JLabel(this.getTurnColorString(turn) + "'s turn");
    	topPanel.add(quit);
    	topPanel.add(colorBlindButton);
    	topPanel.add(currentTurn);
    	topPanel.add(rules);
    	topPanel.add(reserve);
    	
    	newGame = new JButton("New Game");
    	newGame.addActionListener(e -> {newGame();});
    	topPanel.add(newGame);
    	
    	this.setSize(500,500);
    	
    	topPanel.setLayout(new FlowLayout());
    	topPanel.setSize(200,200);
    	
    	gameBoard.setLayout(new GridLayout(rows, columns));
    	gameBoard.setSize(800,800);
    	
    	gameSpaces = new GameSpace[rows][columns];
    	for (int y = 0; y < rows; y++) {
    		for (int x = 0 ; x < columns; x++) {
    			gameSpaces[x][y] = new GameSpace(x, y);
    			gameSpaces[x][y].setSize(20,20);
    			gameSpaces[x][y].setOpaque(true);
    			gameSpaces[x][y].setBorderPainted(true);
    			gameSpaces[x][y].addActionListener(this);
    			if (gameSpaces[x][y].getColor() != Color.black) {
    			   setupColor = gameSpaces[x][y].initialColor();
    			   gameSpaces[x][y].addPiece(new GamePiece(setupColor));
    			   gameSpaces[x][y].updateVisual();
    			     			
    			    }
    			gameBoard.add(gameSpaces[x][y]);
    			}
    			}
    	reserveInfo = new JLabel("<html>Reserve:<br/>Red: 0<br/>Green: 0<br/>Blue: 0<br/>Yellow: 0<html>");
    	reserveInfo.setForeground(Color.white);
    		

    	gameSpaces[7][0].add(reserveInfo);
    	colorKey = new JLabel(" ");
    	gameSpaces[7][7].add(colorKey);


    	playerInfo = new JLabel("<html>Player 1 (Red): " + players[0].getTypeString() + " <br/>Player 2 (Green): " + players[1].getTypeString() +
    			"<br/>Player 3 (Blue): " + players[2].getTypeString() + "<br/>Player 4 (Yellow): " + players[3].getTypeString());
    	playerInfo.setForeground(Color.white);
    	gameSpaces[0][0].add(playerInfo);


    	turnTracker = new JLabel("<HTML>Last 3 moves:<br/>(newest at bottom)<HTML>");
    	turnTracker.setForeground(Color.white);
    	gameSpaces[0][7].add(turnTracker);


    	getContentPane().setLayout(new BorderLayout());
		getContentPane().add(topPanel, BorderLayout.NORTH);
		getContentPane().add(rightPanel, BorderLayout.EAST);
		getContentPane().add(leftPanel, BorderLayout.WEST);
		getContentPane().add(gameBoard, BorderLayout.CENTER);
		
		
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(true);
		setVisible(true);
		
		if (!(currentPlayer.getType() == 0)) { //first move is AI
    		this.moveAI();
    	}
   }

    public void highlightLegal(GameSpace moveFrom) {
		int x = moveFrom.getXcoord();
		int y = moveFrom.getYcoord();
		for (int i = 1; i < highlightHeight + 1; i++) {
			if (x + i < 8) {
				if (!gameSpaces[x + i][y].getColor().equals(Color.black)) {
					if (gameSpaces[x + i][y].getBackground().equals(Color.white)) {
						gameSpaces[x + i][y].setBackground(Color.lightGray);
					}
					else { gameSpaces[x + i][y].setBackground(Color.white); }
				}
			}
			if (x - i > -1) {
				if (!gameSpaces[x - i][y].getColor().equals(Color.black)) {
					if (gameSpaces[x - i][y].getBackground().equals(Color.white)) {
						gameSpaces[x - i][y].setBackground(Color.lightGray);
					}
					else { gameSpaces[x - i][y].setBackground(Color.white); }
				}
			}
			if (y + i < 8) {
				if (!gameSpaces[x][y + i].getColor().equals(Color.black)) {
					if (gameSpaces[x][y + i].getBackground().equals(Color.white)) {
						gameSpaces[x][y + i].setBackground(Color.lightGray);
					}
					else { gameSpaces[x][y + i].setBackground(Color.white); }
				}
			}
			if (y - i > -1) {
				if (!gameSpaces[x][y - i].getColor().equals(Color.black)) {
					if (gameSpaces[x][y - i].getBackground().equals(Color.white)) {
						gameSpaces[x][y - i].setBackground(Color.lightGray);
					}
					else { gameSpaces[x][y - i].setBackground(Color.white); }
				}
			}
		}
	}  

    public void updateReserveInfo() {
    	reserveInfo.setText("<html>Reserve:<br/>Red: " + players[0].getReserve() + "<br/>Green: " + players[1].getReserve() + "<br/>Blue: " +
    			players[2].getReserve() + "<br/>Yellow: "+ players[3].getReserve() + "<html>");
    }
    
    public void nextTurn() {
    	int previousTurn = turn;
    	if (turn == 3) {
    		turn = 0;
    	}else {
    		turn++;
    	}
    	currentPlayer = players[turn];
    	if (noMoveCount == 3) {
    		declareWinner.setText(this.getTurnColorString(turn) + " wins!");
        	currentTurn.setText("Click New Game to play again");
        	gameWon = true;
    	}else {
	    	if (!(this.isMovePossible())) {
	    		noMoveCount++;
	    		this.nextTurn();
	    	}else if (!(gameWon)) {
	    		noMoveCount = 0;
		    	currentTurn.setText(this.getTurnColorString(turn) + "'s turn");
		    	this.updateTurnTracker(previousTurn);
		    	if (!(currentPlayer.getType() == 0)) {
		    		this.moveAI();
		    	}
	    	}
    	}
    }
    
    public void updateTurnTracker(int previousTurn) {
    	String from = "";
    	if (lastMoveWasReserve) {
    		from = "reserve";
    	}else {
    		from = "(" + moveFrom.getXcoord() + ", " + (7 - moveFrom.getYcoord()) + ")";
    	}
    	thirdLastTurn = secondLastTurn;
    	secondLastTurn = lastTurn;
    	lastTurn = (this.getTurnColorString(previousTurn) + ": " + from + " to (" + moveTo.getXcoord() + ", " + (7 - moveTo.getYcoord()) + ")");
    	turnTracker.setText("<html>Last 3 moves:<br/>" + thirdLastTurn + "<br/>" + secondLastTurn + "<br/>" + lastTurn + "<br/>Note: this square is (0, 0)<html>");
    	turnTracker.setForeground(Color.white);
    }
    
    public boolean isMovePossible() {
    	if (currentPlayer.getReserve() > 0) {
    		return true; //player can move if they have reserve
    	}
    	for (int y = 0; y < rows; y++) {
	    	for (int x = 0 ; x < columns; x++) {
	    		if (gameSpaces[x][y].getStackSize() > 0) {
	    			if (gameSpaces[x][y].topPiece().getColor().equals(currentPlayer.getColor())) {
	    				return true; //player has no reserve but they top a space so they can move
	    			}
	    		}
	    	}
    	}
    	return false; //player has no reserve and tops no spaces, no moves are possible
    }
    
    public void newGame() {
    	dispose();
    	new StartMenu();
    }
    
    public Color getTurnColor() {
    	// returns color of player whose turn it currently is
    	return currentPlayer.getColor();
    }
    
    public String getTurnColorString(int turnNumber) {
    	// returns color of player whose turn it currently is
    	if (turnNumber == 0) {
    		return "red";
    	}
    	if (turnNumber == 1) {
    		return "green";
    	}
    	if (turnNumber == 2) {
    		return "blue";
    	}
    	if (turnNumber == 3) {
    		return "yellow";
    	}
    	return null;
    }

 	public void rules() {
		JFrame infoMenu = new JFrame("Rules");
		infoMenu.setSize(500,700);
		infoMenu.setVisible(true);
		infoMenu.getContentPane().add(ruleText);
    }
    
    public void setColorBlind() {
    	if (colorBlindOn) {
			for (int y = 0; y < rows; y++) {
		    	for (int x = 0 ; x < columns; x++) {
		    		if (!(gameSpaces[x][y].getColor().equals(Color.black))) {
			    		for (int i = 0; i < 5; i++) {
			    			int j = (gameSpaces[x][y].getStackSize() - 1) - i;
			    			if (gameSpaces[x][y].getPieceColor(i).equals(Color.red)) {
			    				gameSpaces[x][y].getLabel(j).setText("O O O O O");
			    			}else if (gameSpaces[x][y].getPieceColor(i).equals(Color.cyan)) {
			    				gameSpaces[x][y].getLabel(j).setText("| | | | |");
			    			}else if (gameSpaces[x][y].getPieceColor(i).equals(Color.yellow)) {
			    				gameSpaces[x][y].getLabel(j).setText("- - - - -");
			    			}else if (gameSpaces[x][y].getPieceColor(i).equals(Color.green)) {
			    				gameSpaces[x][y].getLabel(j).setText("X X X X X");
			    			}else if (gameSpaces[x][y].getPieceColor(i).equals(Color.white)) {
			    				gameSpaces[x][y].getLabel(i).setText(" ");
			    			}
			    		}
		    		}
		    	}
			}
		}else {
			for (int y = 0; y < rows; y++) {
		   		for (int x = 0 ; x < columns; x++) {
		   			if (!(gameSpaces[x][y].getColor().equals(Color.black))) {
		   				for (int i = 0; i < 5; i++) {
		   					gameSpaces[x][y].getLabel(i).setText(" ");
		   				}
		    		}
		    	}
			}
		}
    }
    
    public void moveAI() {
    	ArrayList<Integer> fromX = new ArrayList<Integer>();
    	ArrayList<Integer> fromY = new ArrayList<Integer>();
    	for (int y = 0; y < rows; y++) {
	   		for (int x = 0 ; x < columns; x++) {
	   			if (gameSpaces[x][y].getStackSize() > 0) {
	   				if (gameSpaces[x][y].topPiece().getColor().equals(this.getTurnColor())) {
	   					fromX.add(x);
	   					fromY.add(y);
	   				}
	   			}
	   		}
    	}
    	int chooseMoveFrom = 0;
    	int chooseMoveTo = 0;
    	Random rand = new Random();
    	if (currentPlayer.getReserve() > 0) {
    		chooseMoveFrom = rand.nextInt(fromX.size() + 1);
    	}else {
    		chooseMoveFrom = rand.nextInt(fromX.size());
    	}
    	if (chooseMoveFrom == fromX.size()) {
    		//make reserve move
    		lastMoveWasReserve = true;
    		if (currentPlayer.getType() == 1) {
    			//easy version
	    		chooseMoveTo = rand.nextInt(52); //There are 52 white spaces and 12 black. This chooses a white space.
	    		int i = 0;
	    		for (int y = 0; y < rows; y++) {
	    	   		for (int x = 0 ; x < columns; x++) {
	    	   			if (!(gameSpaces[x][y].getColor().equals(Color.black))) {
	    	   				if (i == chooseMoveTo) {
	    	   					moveHandler.makeReserveMove(gameSpaces[x][y], currentPlayer);
	    	   					this.updateReserveInfo();
								this.nextTurn();
								this.setColorBlind();
	    	   				}
	    	   				i++;
	    	   			}
	    	   		}
	    		}
    		}else {
    			//hard version
    			chooseMoveTo = rand.nextInt(52); //There are 52 white spaces and 12 black. This chooses a white space.
	    		int i = 0;
	    		boolean goodMove = false;
	    		while (!(goodMove)) {
		    		for (int y = 0; y < rows; y++) {
		    	   		for (int x = 0 ; x < columns; x++) {
		    	   			if (!(gameSpaces[x][y].getColor().equals(Color.black))) {
		    	   				if ((i == chooseMoveTo) && (gameSpaces[x][y].getStackSize() > 0)) {
		    	   					if (!(gameSpaces[x][y].topPiece().getColor().equals(currentPlayer.getColor()))) {
		    	   						goodMove = true;
			    	   					moveHandler.makeReserveMove(gameSpaces[x][y], currentPlayer);
			    	   					this.updateReserveInfo();
										this.nextTurn();
										this.setColorBlind();
		    	   					}
		    	   				}
		    	   				i++;
		    	   			}
		    	   		}
		    		}
	    		}
    		}
    	}else {
    		//make normal move
    		lastMoveWasReserve = false;
    		moveFrom = gameSpaces[fromX.get(chooseMoveFrom)][fromY.get(chooseMoveFrom)];
    		int x = moveFrom.getXcoord();
    		int y = moveFrom.getYcoord();
    		boolean valid = false;
    		int distance = 0;
    		int tryIdealMove = 0;
    		int idealAttemptLimit = 2;
    		//Hard AI will try to pick an ideal move to make by checking random moves. If it fails to find an ideal move 2 times it will make a random move.
    		if (currentPlayer.getType() == 1) {
    			tryIdealMove = idealAttemptLimit; //Easy AI does not attempt ideal moves.
    		}
    		while (!(valid)) {
    			distance = (rand.nextInt(moveFrom.getStackSize()) + 1);
        		int direction = rand.nextInt(4);
    			if (direction == 0) {
    				if ((x + distance) < 8) {
	    				if (!(gameSpaces[x + distance][y].getColor().equals(Color.black))) {
	    					if ((gameSpaces[x + distance][y].getStackSize() > 0) || (tryIdealMove >= idealAttemptLimit)) {
	    						if (!((tryIdealMove < idealAttemptLimit) && (gameSpaces[x + distance][y].topPiece().getColor().equals(currentPlayer.getColor())))) {
		    					valid = true;
		    					moveTo = gameSpaces[x + distance][y];
	    						}
	    					}
	    				}
    				}
    			}else if (direction == 1) {
    				if ((x - distance) >= 0) {
	    				if (!(gameSpaces[x - distance][y].getColor().equals(Color.black))) {
	    					if ((gameSpaces[x - distance][y].getStackSize() > 0) || (tryIdealMove >= idealAttemptLimit)) {
	    						if (!((tryIdealMove < idealAttemptLimit) && (gameSpaces[x - distance][y].topPiece().getColor().equals(currentPlayer.getColor())))) {
		    					valid = true;
		    					moveTo = gameSpaces[x - distance][y];
	    						}
	    					}
	    				}
    				}
    			}else if (direction == 2) {
    				if ((y + distance) < 8) {
	    				if (!(gameSpaces[x][y + distance].getColor().equals(Color.black))) {
	    					if ((gameSpaces[x][y + distance].getStackSize() > 0) || (tryIdealMove >= idealAttemptLimit)) {
	    						if (!((tryIdealMove < idealAttemptLimit) && (gameSpaces[x][y + distance].topPiece().getColor().equals(currentPlayer.getColor())))) {
		    					valid = true;
		    					moveTo = gameSpaces[x][y + distance];
	    						}
	    					}
	    				}
    				}
    			}else {
    				if ((y - distance) >= 0) {
	    				if (!(gameSpaces[x][y - distance].getColor().equals(Color.black))) {
	    					if ((gameSpaces[x][y - distance].getStackSize() > 0) || (tryIdealMove >= idealAttemptLimit)) {
	    						if (!((tryIdealMove < idealAttemptLimit) && (gameSpaces[x][y - distance].topPiece().getColor().equals(currentPlayer.getColor())))) {
		    					valid = true;
		    					moveTo = gameSpaces[x][y - distance];
	    						}
	    					}
	    				}
    				}
    			}
    			tryIdealMove++;
    		}
    		moveHandler.makeMove(moveTo, moveFrom, currentPlayer, distance);
			this.updateReserveInfo();
			this.nextTurn();
			this.setColorBlind();
    	}
    }
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		Object selected = e.getSource();
		if(selected.equals(quit)){ System.exit(0); } // quit

		if (selected.equals(colorBlindButton)) {
			if (colorBlindOn) {
				colorBlindOn = false;
				colorBlindInfo.setText(" ");
				colorKey.setText(" ");
			}else {
				colorBlindOn = true;
				colorBlindInfo.setText("Color Blind Mode is Active");
				colorKey.setText("<html>Color key:<br/>Red: O<br/>Green: X<br/>Blue: |<br/>Yellow: -<html>");
				colorKey.setForeground(Color.white);
			}
			this.setColorBlind();
		}
		if (selected.equals(reserve)) {
			if (!(gameWon) && (currentPlayer.getType() == 0)) {
				if (!(moveFromSelected) && reserve.getBackground().equals(defaultButtonColor) && (currentPlayer.getReserve() > 0)) {
					reserve.setBackground(Color.gray);
					moveFromSelected = true;
				}else if (moveFromSelected && reserve.getBackground().equals(Color.gray)) {
					reserve.setBackground(defaultButtonColor);
					moveFromSelected = false;
				}
			}
		}
		if (selected instanceof GameSpace) {
			if (!(gameWon) && (currentPlayer.getType() == 0)) {
				if (moveFromSelected) {
					moveTo = (GameSpace) selected;
					if (!(moveTo.getColor().equals(Color.black))) {
						if (reserve.getBackground().equals(Color.gray)) {
							//make reserve move
							lastMoveWasReserve = true;
							reserve.setBackground(defaultButtonColor);
							moveFromSelected = false;
							moveHandler.makeReserveMove(moveTo, currentPlayer);
							this.updateReserveInfo();
							this.nextTurn();
							this.setColorBlind();
						}else if (moveTo.equals(moveFrom)) {
							//unselect space
							moveFromSelected = false;
							moveFrom.setBackground(Color.white);
							highlightLegal(moveFrom);
						}else {
							//space has been selected to move to
							lastMoveWasReserve = false;
							int xDist = Math.abs(moveTo.getXcoord() - moveFrom.getXcoord());
							int yDist = Math.abs(moveTo.getYcoord() - moveFrom.getYcoord());
							int distance = xDist + yDist;
							if ((distance <= moveFrom.getStackSize()) && ((xDist == 0) || (yDist == 0))) {
								moveFromSelected = false;
								moveFrom.setBackground(Color.white);
								highlightLegal(moveFrom);
								moveHandler.makeMove(moveTo, moveFrom, currentPlayer, distance);
								this.updateReserveInfo();
								this.nextTurn();
								this.setColorBlind();
							}
						}
					}
				}else {
					//space has been selected to move from
					moveFrom = (GameSpace) selected;
					if (!(moveFrom.getColor().equals(Color.black)) && (moveFrom.getStackSize() > 0)) {
						if (moveFrom.topPiece().getColor().equals(this.getTurnColor())) {
							moveFromSelected = true;
							moveFrom.setBackground(Color.darkGray);
							highlightHeight = moveFrom.getStackSize();
							highlightLegal(moveFrom);
						}
					}
				}
			}
		}
	}
}
