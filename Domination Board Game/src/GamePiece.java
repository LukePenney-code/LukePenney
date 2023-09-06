import java.awt.*;
import java.io.Serializable;

import javax.swing.*;
public class GamePiece implements Serializable{
	
	private Color color;
	/**
	 * @param color 
	 */
	public GamePiece(Color color) {
		this.color = color;
	}
	
	public Color getColor() {
		return color;
	}
	
	public void setColor(Color newColor) {
		this.color = newColor;
	}
}