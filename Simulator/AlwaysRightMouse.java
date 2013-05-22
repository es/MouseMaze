
public AlwaysRightMouse extends Mouse {
	public AlwaysRightMouse (int mouseX, int mouseY, int mouseDirection, Simulator sim) {
		super(int mouseX, int mouseY, int mouseDirection, Simulator sim);
	}

	public void logic () {
		while (!isFinished()) {
			if (rightOpen()) {
				turnRight();
				goForward();
			}	
			else if (!forwardOpen())
				turnLeft();
			else
				goForward();
			//printMaze();
		}
	}
}