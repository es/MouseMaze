
public class RandomMouse extends Mouse {
	public RandomMouse (int mouseX, int mouseY, int mouseDirection, Simulator sim) {
		super (int mouseX, int mouseY, int mouseDirection, Simulator sim);
	}

	public void Logic () {
		double r;
		while (!sim.isFinished()) {
			if (sim.rightOpen(mouseX, mouseY, mouseDirection)&&sim.forwardOpen(mouseX, mouseY, mouseDirection)&&sim.leftOpen(mouseX, mouseY, mouseDirection)) {
				r=Math.random();
				if (r<0.3)
					turnLeft();
				else {
					if (r<0.6) 
						turnRight();
				}
				goForward();
			}	
			else if (sim.forwardOpen(mouseX, mouseY, mouseDirection)&&sim.leftOpen(mouseX, mouseY, mouseDirection)) {
				r=Math.random();
				if (r<0.5)
					turnLeft();
				goForward();
			}
			else if (sim.rightOpen(mouseX, mouseY, mouseDirection)&&sim.forwardOpen(mouseX, mouseY, mouseDirection)) {
				r=Math.random();
				if (r<0.5)
					turnRight();
				goForward();
			}
			else if (sim.rightOpen(mouseX, mouseY, mouseDirection)&&sim.leftOpen(mouseX, mouseY, mouseDirection)) {
				r=Math.random();
				if (r<0.5)
					turnRight();
				else
					turnLeft();
				goForward();
			}
			else if (sim.leftOpen(mouseX, mouseY, mouseDirection)) {
				turnLeft();
				goForward();
			}
			else if (sim.rightOpen(mouseX, mouseY, mouseDirection)) {
				turnRight();
				goForward();
			}
			else if (sim.forwardOpen(mouseX, mouseY, mouseDirection)) {
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