
public AlwaysRightMouse extends Mouse {
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