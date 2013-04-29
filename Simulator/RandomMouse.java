
public class RandomMouse extends Mouse {
	public void Logic () {
		double r;
		while (!isFinished()) {
			if (rightOpen()&&forwardOpen()&&leftOpen()) {
				r=Math.random();
				if (r<0.3)
					turnLeft();
				else {
					if (r<0.6) 
						turnRight();
				}
				goForward();
			}	
			else if (forwardOpen()&&leftOpen()) {
				r=Math.random();
				if (r<0.5)
					turnLeft();
				goForward();
			}
			else if (rightOpen()&&forwardOpen()) {
				r=Math.random();
				if (r<0.5)
					turnRight();
				goForward();
			}
			else if (rightOpen()&&leftOpen()) {
				r=Math.random();
				if (r<0.5)
					turnRight();
				else
					turnLeft();
				goForward();
			}
			else if (leftOpen()) {
				turnLeft();
				goForward();
			}
			else if (rightOpen()) {
				turnRight();
				goForward();
			}
			else if (forwardOpen()) {
				goForward();
			}
			else { //Dead End
				turnRight();
				turnRight();
				goForward();
			}
			//printMaze();
		}
	}
}