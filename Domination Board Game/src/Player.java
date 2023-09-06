import java.awt.Color;
import java.io.Serializable;

public class Player implements Serializable {
	
	private int type; // 0 for human, 1 for easy, 2 for hard
	private Color color;
	private int reserve;
	
	public Player(int type , Color color) {
		this.color = color;
		this.type = type;
	}
	
	public Color getColor() {
		return this.color;
	}
	
	public int getReserve() {
		return this.reserve;
	}
	
	public void incrementReserve(int amount) {
		reserve = reserve + amount;
	}
	
	public void decrementReserve() {
		reserve--;
	}
	
	public int getType() {
		return this.type;
	}
	
	public void setType(int new_type) {    //0, 1, or 2
		this.type = new_type;
	}
	
	public String getTypeString() {
		if (this.type == 0) {
			return "Human";
		}else if (this.type == 1) {
			return "Easy AI";
		}else {
			return "Hard AI";
		}
	}
	
	public boolean isAIPlayer() {
		if(getType() == 1) {
			return true;
		}
		else if( getType()==2) {
			return true;
		}
		else {
			return false;
		}
	}
}