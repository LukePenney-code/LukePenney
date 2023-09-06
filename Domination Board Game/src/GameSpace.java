import javax.swing.*;
import java.awt.*;
import java.io.Serializable;
import java.util.ArrayList;

public class GameSpace extends JButton implements Serializable{
	private ArrayList<GamePiece> stack;
	private int xcoord, ycoord, i;
	private JPanel[] panels;
	private JLabel[] labels;
	
	/**
	 * @param stack
	 */
	public GameSpace(int xcoord, int ycoord) {
		super();
		this.xcoord = xcoord;
		this.ycoord = ycoord;
		stack = new ArrayList<GamePiece>();
		//spaces that are not part of the game are black, otherwise spaces are white
		if (((xcoord == 0) || (xcoord == 7)) && ((ycoord > 5) || (ycoord < 2))) {
			this.setBackground(Color.black);
		}else if (((xcoord == 1) || (xcoord == 6)) && ((ycoord == 7) || (ycoord == 0))) {
			this.setBackground(Color.black);
		} else {
			this.setBackground(Color.white);
		}
		this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		//add panels to all white spaces to use for visual representation of pieces
		panels = new JPanel[5];
		labels = new JLabel[5];
		i = 0;
		if (this.getBackground().equals(Color.white)) {
			while (i < 5) {
				panels[i] = new JPanel();
				labels[i] = new JLabel(" ");
				labels[i].setFont(new Font("Serif", Font.BOLD, 7));
				panels[i].setBackground(Color.white);
				panels[i].add(labels[i]);
				this.add(panels[i]);
				i++;
			}
		}
	}


	public int getStackSize() {
		return stack.size();
	}
	
	public GamePiece topPiece() {
		return stack.get(stack.size() - 1);
	}
	
	public void removeBot() {
		// removes the bottom piece
		stack.remove(0);
	}
	
	public void removeTop() {
		// removes the top piece
		stack.remove(stack.size() - 1);
	}
	
	public void addPiece(GamePiece newPiece) {
		stack.add(newPiece);
	}

	public int getXcoord() {
		return xcoord;
	}

	public void setXcoord(int xcoord) {
		this.xcoord = xcoord;
	}

	public int getYcoord() {
		return ycoord;
	}

	public void setYcoord(int ycoord) {
		this.ycoord = ycoord;
	}
	
	public Color getColor() {
		return this.getBackground();
	}
	
	public int updateStack(Color currentTurnColor) {
		//Deals with oversized stack. Returns the number of pieces to add to reserve.
		int toReturn = 0;
		while (this.getStackSize() > 5) {
			if (this.getPieceColor(0).equals(currentTurnColor)) {
				toReturn++;
			}
			this.removeBot();
		}
		return toReturn;
	}
	public void updateVisual() {
		//Update panel colors
		int i = this.getStackSize() - 1;
		int j = 0;
		while (i >= 0) {
			panels[j].setBackground(stack.get(i).getColor());
			i--;
			j++;
		}
		i = this.getStackSize();
		while (i < 5) {
			panels[j].setBackground(Color.white);
			i++;
			j++;
		}
	}
	
	public JLabel getLabel(int i) {
		return this.labels[i];
	}
	
	public Color getPieceColor(int i) {
		if (i < this.getStackSize()) {
			return stack.get(i).getColor();
		}else {
			return Color.white;
		}
	}
	
	public Color initialColor() {
		// returns the color that the piece that starts on this space at the beginning of the game should be set to
		if ((xcoord < 4) && ((ycoord == 2) || (ycoord == 0))) {
			return Color.cyan;
		}else if (((xcoord == 1) || (xcoord == 3)) && (ycoord > 3)) {
			return Color.cyan;
		}else if ((xcoord > 3) && ((ycoord == 7) || (ycoord == 5))) {
			return Color.red;
		}else if (((xcoord == 4) || (xcoord == 6)) && (ycoord < 4)) {
			return Color.red;
		}else if ((xcoord < 4) && ((ycoord == 3) || (ycoord == 1))) {
			return Color.yellow;
		}else if (((xcoord == 5) || (xcoord == 7)) && (ycoord < 4)) {
			return Color.yellow;
		}else {
			return Color.green;
		}
	}
}
