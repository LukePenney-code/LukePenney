   
import java.io.Serializable;

import javax.swing.UIManager;

public class Launcher implements Serializable {
	public static void main(String[] args) {
		try {
			UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
		}
		catch(Exception e) {
			e.printStackTrace();
		}
		new StartMenu();
		
	}
}
