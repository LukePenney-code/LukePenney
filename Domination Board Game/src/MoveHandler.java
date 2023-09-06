import java.io.Serializable;
import java.util.ArrayList;

public class MoveHandler implements Serializable {
	
	private ArrayList<GamePiece> transferStack;
	
	public MoveHandler() {
		//This constructor does nothing
	}
	
	public void makeReserveMove(GameSpace moveTo, Player currentPlayer) {
		currentPlayer.decrementReserve();
		moveTo.addPiece(new GamePiece(currentPlayer.getColor()));
		int toReserve = moveTo.updateStack(currentPlayer.getColor()); //updateStack must come before updateVisual
		currentPlayer.incrementReserve(toReserve);
		moveTo.updateVisual();
    }
    
    public void makeMove(GameSpace moveTo, GameSpace moveFrom, Player currentPlayer, int distance) {
    	transferStack = new ArrayList<GamePiece>();
		int i = 0;
		while (i < distance) {
			transferStack.add(moveFrom.topPiece());
			moveFrom.removeTop();
			i++;
		}
		i--;
		while (i >= 0) {
			moveTo.addPiece(transferStack.get(i));
			i--;
		}
		moveFrom.updateVisual();
		int toReserve = moveTo.updateStack(currentPlayer.getColor());
		currentPlayer.incrementReserve(toReserve);
		moveTo.updateVisual();
    }
}
