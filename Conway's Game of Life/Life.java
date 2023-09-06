import java.awt.*;
import java.util.Random;

class Life {

	private int[][] old;
	private int n, dimensions, magnification, rows, cols;
	private String config;
	private Picture pic;

	// Constructor for Life Class
	// @param n is the number of iterations
	// @param dimensions is the size of the grid
	// @param config is the starting configuration of the board "R" for random, "S" for Simkin Glider Gun, "P" for penta decathalon oscillator, "G" for Gosper Glider gun
	// Luke Penney 09/23/2022
	public Life(int n, int dimensions, String config) {
		this.n = n;
		this.dimensions = dimensions;
		this.config = config;
		this.magnification = 10;
		this.rows = dimensions;
		this.cols = dimensions;
		old = new int[dimensions][dimensions];
		pic = new Picture(dimensions * magnification, dimensions * magnification);
		startConfiguration(config);
		for (int i = 0; i < n; i++) {

			automata();

		}

	}

	// Method draws black cells
	private void drawCellBlack(int i, int j) {

		Color col = new Color(0, 0, 0);

		for (int offsetX = 0; offsetX < magnification; offsetX++) {
			for (int offsetY = 0; offsetY < magnification; offsetY++) {
				// set() colours an individual pixel
				pic.set((i * magnification) + offsetX,
						(j * magnification) + offsetY, col);
			}
		}
	}

	// Method draws white cells
	private void drawCellWhite(int i, int j) {

		Color col = new Color(255, 255, 255);

		for (int offsetX = 0; offsetX < magnification; offsetX++) {
			for (int offsetY = 0; offsetY < magnification; offsetY++) {
				// set() colours an individual pixel
				pic.set((i * magnification) + offsetX,
						(j * magnification) + offsetY, col);
			}
		}
	}

	public void show() {
		pic.show();

	}

	// This method seeds the intial starting board configuration
	public void startConfiguration(String config) {

		// Random starting configuration
		if (config.equals("R")) {
			Random rand = new Random();
			for (int i = 0; i < old.length; i++) {
				for (int j = 0; j < old.length; j++) {
					old[i][j] = (int) Math.floor(rand.nextInt(2));

				}
			}

		}
		// Penta decathalon starting configuration
		if (config.equals("P")) {

			// center pixels of the grid
			int centerX = this.rows / 2;
			int centerY = this.cols / 2;

			old[centerX][centerY] = 1;
			old[centerX - 1][centerY] = 1;
			old[centerX + 1][centerY] = 1;
			old[centerX + 2][centerY] = 1;
			old[centerX - 2][centerY - 1] = 1;
			old[centerX + 3][centerY - 1] = 1;
			old[centerX - 2][centerY + 1] = 1;

			old[centerX + 3][centerY - 1] = 1;
			old[centerX + 3][centerY + 1] = 1;
			old[centerX + 4][centerY] = 1;
			old[centerX + 5][centerY] = 1;
			old[centerX - 3][centerY] = 1;
			old[centerX - 4][centerY] = 1;
		}

		/* 
		 * Bonus I accidentally implemented this by accident and it was too coo to delete so I kept it
		*/
		// Gosper glider starting configuration
		if (config.equals("G")) {

			// Setting the start values for glider gun config
			old[26][2] = 1;
			old[24][3] = 1;
			old[26][3] = 1;
			old[14][4] = 1;
			old[15][4] = 1;
			old[22][4] = 1;
			old[23][4] = 1;
			old[36][4] = 1;
			old[37][4] = 1;
			old[13][5] = 1;
			old[17][5] = 1;
			old[22][5] = 1;
			old[23][5] = 1;
			old[36][5] = 1;
			old[37][5] = 1;
			old[2][6] = 1;
			old[3][6] = 1;
			old[12][6] = 1;
			old[18][6] = 1;
			old[22][6] = 1;
			old[23][6] = 1;
			old[2][7] = 1;
			old[3][7] = 1;
			old[12][7] = 1;
			old[16][7] = 1;
			old[18][7] = 1;
			old[19][7] = 1;
			old[24][7] = 1;
			old[26][7] = 1;
			old[12][8] = 1;
			old[18][8] = 1;
			old[26][8] = 1;
			old[13][9] = 1;
			old[17][9] = 1;
			old[14][10] = 1;
			old[15][10] = 1;

		}

        // Simkin Glider gun starting configuration
		if (config.equals("S")) {
			// Square 1
			old[1][1] = 1;
			old[2][1] = 1;
			old[1][2] = 1;
			old[2][2] = 1;
			// Square 2
			old[5][4] = 1;
			old[5][5] = 1;
			old[6][4] = 1;
			old[6][5] = 1;
			// Square 3
			old[8][21] = 1;
			old[8][2] = 1;
			old[9][1] = 1;
			old[9][2] = 1;
			// Square 4
			old[25][14] = 1;
			old[25][15] = 1;
			old[26][14] = 1;
			old[26][15] = 1;
			// Square 5
			old[32][14] = 1;
			old[32][15] = 1;
			old[33][14] = 1;
			old[33][15] = 1;
			// Square 6
			old[28][11] = 1;
			old[28][12] = 1;
			old[29][11] = 1;
			old[29][12] = 1;
			// Shape 
			old[20][1] = 1;
			old[20][2] = 1;
			old[20][3] = 1;
			old[19][2] = 1;
			old[18][2] = 1;
			old[18][3] = 1;
			old[18][4] = 1;


		}

	}

	// Counts the number of alive neighbors at each state
	public int countNeighbors(int[][] grid, int x, int y) {
		int sum = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				// wrap around functionality
				int col = (x + i + this.cols) % this.cols;
				int row = (y + j + this.rows) % this.rows;
				// summing up all alive neighbors
				sum += grid[col][row];
			}

		}
		sum -= grid[x][y];

		return sum;

	}

	// Computes the game of life
	public void automata() {

		// Updated grid
		int[][] newB = new int[dimensions][dimensions];
		// Iterates through the current game board and applies the game of life
		for (int i = 0; i < old.length; i++) {
			for (int j = 0; j < old.length; j++) {

				int numNeighbors = countNeighbors(old, i, j);
				int state = old[i][j];
				if (state == 1 && numNeighbors < 2 || numNeighbors > 3) {
					newB[i][j] = 0;
				} 
			    else if (state == 0 && numNeighbors == 3) {
					newB[i][j] = 1;

				} else {
					newB[i][j] = state;
				}	

			}

		}
		// Setting the new values to the old values after rules are applied
		old = newB;

		// Redraws the game board after the rules are applied
		for (int x = 0; x < old.length; x++) {
			for (int y = 0; y < old.length; y++) {
				if (newB[x][y] == 1) {
					drawCellBlack(x, y);
				} else {
					drawCellWhite(x, y);
				}
			}

		}

		show();


	}

	public static void main(String[] args) throws InterruptedException {
		// TODO Auto-generated method stub

		int n = Integer.parseInt(args[0]);
		int dimensions = Integer.parseInt(args[1]);
		String config = args[2];
		Thread.sleep(3000);
		new Life(n, dimensions, config);

	}

}
