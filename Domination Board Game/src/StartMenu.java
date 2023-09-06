import javax.swing.*;
import javax.swing.border.Border;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.Serializable;

public class StartMenu implements ActionListener, Serializable{
	private JLabel title, prompt, rules;
	private JFrame frame;
	private JButton start, quit, easy, easy2, easy3, easy4, human1, human2, human3, human4, ruleButton;
	private ImageIcon logo;
	private int player_one_type, player_two_type, player_three_type, player_four_type;
	private GameBoard game;
	
	
	public StartMenu() {
		
		title = new JLabel("Domination!");
		prompt = new JLabel("Player 1           Player 2           Player 3          Player 4");
		frame = new JFrame("Start Menu");
		frame.setSize(850,870);
		frame.setVisible(true);
		logo = new ImageIcon("C://Users//Luke Penney//Pictures//workingLogo.png");
		setUpLabel(frame,title,prompt,logo);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		
		ruleButton = new JButton("Rules");
		start = new JButton("Start");
		//load = new JButton("Load");
		quit = new JButton("Quit");
		setUpButtons(frame, start, ruleButton, quit);
		//hard = new JButton("Hard");
		easy = new JButton("AI");
		easy2 = new JButton("AI");
		//hard2 = new JButton("Hard");
		easy3 = new JButton("AI");
		//hard3 = new JButton("Hard");
		easy4 = new JButton("AI");
		//hard4 = new JButton("Hard");
		human1 = new JButton("Human");
		human2 = new JButton("Human");
		human3 = new JButton("Human");
		human4 = new JButton("Human");
		rules = new JLabel("<html>-This game deals with stacks of pieces. A single piece can be considered a stack of height 1.<br>-Stacks may be moved horizontally or vertically, but not diagonally.<br>-A player may only move a stack if the top piece of the stack is of their color.<br>-A stack may be moved up to h spaces, h being the height of the stack. A stack may only be moved in one direction per move, for example, 2 spaces up is permitted but 1 up and 1 left is not.<br>-When a stack is moved x spaces, only the top x pieces of the stack move, for example, if a 5 high stack is moved 3 spaces, the top 3 pieces of the stack move and the other 2 pieces are left behind.<br>-If a player's move causes a stack to grow to a height of more than 5 pieces, then pieces will be removed from the bottom of the stack until the stack has a height of 5. Any removed pieces which are of the player's color are kept as reserve pieces, all other removed pieces are deleted from the game.<br>-Reserve pieces may be placed anywhere on the board.<br>-If a player has no possible moves, their turn is skipped. When only 1 player can move, that player wins.</html>");
		difficultySetting(frame, easy, easy2, easy3, easy4);
		groupMemberNames();
	}


	private void setUpButtons(JFrame frame, JButton start, JButton ruleButton, JButton quit) {
		// TODO Auto-generated method stub
		//ImageIcon startIcon = new ImageIcon("start.png");
		ruleButton.setBounds(20, 300, 100, 100);
		frame.getContentPane().add(ruleButton);
		ruleButton.setBackground(Color.RED);
		ruleButton.setForeground(Color.yellow);
		ruleButton.setFont(new Font("Bahaus 93", Font.PLAIN,20));
		quit.setBounds(20, 410, 100, 100);
		frame.getContentPane().add(quit);
		quit.setBackground(Color.RED);
		quit.setForeground(Color.yellow);
		quit.setFont(new Font("Bahaus 93", Font.PLAIN,20));
		quit.addActionListener(this);
		start.setBounds(700, 550, 110, 100);
		ruleButton.addActionListener(this);
		//start.setIcon(startIcon);
		frame.getContentPane().add(start);
		start.setBackground(Color.RED);
		start.setForeground(Color.yellow);
		start.setFont(new Font("Bahaus 93", Font.PLAIN,20));
		start.addActionListener(this);
		Border emptyBorder = BorderFactory.createEmptyBorder();
		start.setBorder(emptyBorder);
		quit.setBorder(emptyBorder);
		ruleButton.setBorder(emptyBorder);
	}
	
	private void difficultySetting(JFrame frame, JButton easy, JButton easy2, JButton easy3, JButton easy4) {
		
		//Player 1 setup
		
		human1.setBounds(45, 730, 75, 60);
		frame.getContentPane().add(human1);
		human1.setBackground(Color.red);
		human1.setFont(new Font("Bahaus 93", Font.BOLD,12));
		human1.addActionListener(this);
		
		easy.setBounds(45, 670, 75, 60);
		frame.getContentPane().add(easy);
		easy.setBackground(Color.red);
		easy.setFont(new Font("Bahaus 93", Font.BOLD,11));
		easy.addActionListener(this);
		
		//Player 2 setup
		
		human2.setBounds(200, 730, 75, 60);
		frame.getContentPane().add(human2);
		human2.setBackground(Color.green);
		human2.setFont(new Font("Bahaus 93", Font.BOLD,12));
		human2.addActionListener(this);
		
		easy2.setBounds(200, 670, 75, 60);
		frame.getContentPane().add(easy2);
		easy2.setBackground(Color.green);
		easy2.setFont(new Font("Bahaus 93", Font.BOLD,11));
		easy2.addActionListener(this);
		
		//Player 3 setup
		
		human3.setBounds(355, 730, 75, 60);
		frame.getContentPane().add(human3);
		human3.setBackground(Color.cyan);
		human3.setFont(new Font("Bahaus 93", Font.BOLD,12));
		human3.addActionListener(this);
		
		easy3.setBounds(355, 670, 75, 60);
		frame.getContentPane().add(easy3);
		easy3.setBackground(Color.cyan);
		easy3.setFont(new Font("Bahaus 93", Font.BOLD,11));
		easy3.addActionListener(this);


		//Player 4 setup

		human4.setBounds(505, 730, 75, 60);
		frame.getContentPane().add(human4);
		human4.setBackground(new Color(220,220,0));
		human4.setFont(new Font("Bahaus 93", Font.BOLD,12));
		human4.addActionListener(this);
		
		easy4.setBounds(505, 670, 75, 60);
		frame.getContentPane().add(easy4);
		easy4.setBackground(new Color(220,220,0));
		easy4.setFont(new Font("Bahaus 93", Font.BOLD,11));
		easy4.addActionListener(this);
		
	}



	private void setUpLabel(JFrame frame, JLabel title, JLabel prompt, ImageIcon logo) {
		// TODO Auto-generated method stub
		title.setIcon(logo);
		frame.add(title);
		frame.getContentPane().add(prompt);
		title.setVerticalTextPosition(JLabel.TOP);
		title.setHorizontalTextPosition(JLabel.CENTER);
		title.setHorizontalAlignment(JLabel.CENTER);
		title.setFont(new Font("Algerian", Font.BOLD, 75));
		title.setForeground(Color.red);
		title.setBounds(120, 1, 600, 600);
		frame.setLayout(null);
		frame.getContentPane().setBackground(Color.yellow);
		prompt.setBounds(50, 620, 580, 50);
		prompt.setFont(new Font("MV Boli",Font.BOLD,16));
		
	}
	
	public void groupMemberNames() {
		JLabel luke = new JLabel("Luke");
		JLabel evan = new JLabel("Evan");
		JLabel farhan = new JLabel("Farhan");
		JLabel raveen = new JLabel("Raveen");
		frame.getContentPane().add(raveen);
		frame.getContentPane().add(luke);
		frame.getContentPane().add(evan);
		frame.getContentPane().add(farhan);
		luke.setBounds(20, 30, 100, 100);
		luke.setForeground(Color.red);
		luke.setFont(new Font("Algerian", Font.BOLD, 16));
		evan.setBounds(20, 50, 100, 100);
		evan.setForeground(Color.red);
		evan.setFont(new Font("Algerian", Font.BOLD, 16));
		farhan.setBounds(20, 70, 100, 100);
		farhan.setForeground(Color.red);
		farhan.setFont(new Font("Algerian", Font.BOLD, 16));
		raveen.setBounds(20, 90, 100, 100);
		raveen.setForeground(Color.red);
		raveen.setFont(new Font("Algerian", Font.BOLD, 16));
	}



	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		Object selected = e.getSource();
		if(selected == start) {
			new GameBoard(player_one_type, player_two_type, player_three_type, player_four_type);
			frame.dispose();
		}
		if(selected == ruleButton){
			JFrame infoMenu = new JFrame("Rules");
			infoMenu.setSize(500,700);
			infoMenu.setVisible(true);
			infoMenu.getContentPane().add(rules);
		}
		
		if(selected == quit) {
			frame.dispose();
		}
		if(selected == easy) {
			this.player_one_type = 1;
						
		}
		if(selected == easy2) {
			this.player_two_type = 1;
		}
		if(selected == easy3) {
			this.player_three_type = 1;
		}
		if(selected == easy4) {
			this.player_four_type = 1;
		}
		if(selected == human1) {
			this.player_one_type = 0;
		}
		if(selected == human2) {
			this.player_two_type = 0;
		}
		if(selected == human3) {
			this.player_three_type = 0;
		}
		if(selected == human4) {
			this.player_four_type = 0;
		}
	}

}
