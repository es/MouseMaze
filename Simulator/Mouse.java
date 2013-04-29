
public class Mouse {
		public void goForward () throws Exception{
		stepCounter++;
		if (mouseDirection==0) { //up
			if (maze[mouseX][mouseY-1]!=1)
				mouseY--;
			else
				throw new Exception ();
		}
		else if (mouseDirection==1) {//right
			if (maze[mouseX+1][mouseY]!=1)
				mouseX++;
			else
				throw new Exception ();
		}
		else if (mouseDirection==2) {//down
			if (maze[mouseX][mouseY+1]!=1)
				mouseY++;
			else
				throw new Exception ();
		}
		else {//left
			if (maze[mouseX-1][mouseY]!=1)
				mouseX--;
			else
				throw new Exception ();
		}
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
}