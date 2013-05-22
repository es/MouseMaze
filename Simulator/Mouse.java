
public abstract class Mouse {
		int mouseX;
		int mouseY;
		int mouseDirection;//0=Up, 1=Right, 2=Down, 3=Left
		Simulator sim;

		public Mouse (int mouseX, int mouseY, int mouseDirection, Simulator sim) {
			this.sim=sim;
			this.mouseX=mouseX;
			this.mouseY=mouseY;
			this.mouseDirection=mouseDirection;
		}
		
		abstract void logic ();

		public void goForward () throws Exception{
		if (mouseDirection==0) //up
			mouseY--;
		else if (mouseDirection==1) //right
			mouseX++;
		else if (mouseDirection==2) //down
			mouseY++;
		else //left
			mouseX--;
		sim.move(mouseX,mouseY);
	}

	public void turnRight () {
		if (mouseDirection==3)
			mouseDirection=0;
		else
			mouseDirection++;
	}

	public void turnLeft () {
		if (mouseDirection==0)
			mouseDirection=3;
		else
			mouseDirection--;
	} 

	abstract String toString ();
}