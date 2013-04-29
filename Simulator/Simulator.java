import java.util.*;
import java.io.*;

public class Simulator {
	int maze[][]=new int [10][10];//0=open, 1=closed, 2=start, 3=finished
	int mouseX;
	int mouseY;
	int mouseDirection;//0=Up, 1=Right, 2=Down, 3=Left
	int stepCounter;

	public void loadMaze (File document) throws Exception {
		try {
			BufferedReader in=new BufferedReader (new FileReader(document.toString()));
			for (int y=0;y<10;y++) {
				String s=in.readLine();
				char[] temp=s.toCharArray();
				for (int x=0;x<10;x++)
					maze[x][y]=Integer.parseInt(temp[x]+"");
			}
		}
		catch (IOException woops) {
			woops.printStackTrace (System.out);
		}
		HigherLoop: for (int y=0;y<10;y++) {
			for (int x=0;x<10;x++) {
				if (maze[x][y]==2) {
					mouseX=x;
					mouseY=y;
					break HigherLoop;
				}
			}
		}
		if (mouseX==-1||mouseY==-1)
			throw new Exception ();
	}

	public boolean forwardOpen () {
		if (mouseDirection==0)//up
			return 1!=maze[mouseX][mouseY-1]&&maze[mouseX][mouseY-1]!=2;
		else if (mouseDirection==1)//right
			return 1!=maze[mouseX+1][mouseY]&&maze[mouseX+1][mouseY]!=2;
		else if (mouseDirection==2)//down
			return 1!=maze[mouseX][mouseY+1]&&maze[mouseX][mouseY+1]!=2;
		else//left
			return 1!=maze[mouseX-1][mouseY]&&maze[mouseX-1][mouseY]!=2;
	}

	public boolean backwardOpen () {
		if (mouseDirection==0)//up
			return 1!=maze[mouseX][mouseY+1]&&maze[mouseX][mouseY+1]!=2;
		else if (mouseDirection==1)//right
			return 1!=maze[mouseX-1][mouseY]&&maze[mouseX-1][mouseY]!=2;
		else if (mouseDirection==2)//down
			return 1!=maze[mouseX][mouseY-1]&&maze[mouseX][mouseY-1]!=2;
		else//left
			return 1!=maze[mouseX+1][mouseY]&&maze[mouseX+1][mouseY]!=2;
	}

	public boolean leftOpen () {
		if (mouseDirection==0)//up
			return 1!=maze[mouseX-1][mouseY]&&maze[mouseX-1][mouseY]!=2;
		else if (mouseDirection==1)//right
			return 1!=maze[mouseX][mouseY-1]&&maze[mouseX][mouseY-1]!=2;
		else if (mouseDirection==2)//down
			return 1!=maze[mouseX+1][mouseY]&&maze[mouseX+1][mouseY]!=2;
		else//left
			return 1!=maze[mouseX][mouseY+1]&&maze[mouseX][mouseY+1]!=2;
	}

	public boolean rightOpen () {
		if (mouseDirection==0)//up
			return 1!=maze[mouseX+1][mouseY]&&maze[mouseX+1][mouseY]!=2;
		else if (mouseDirection==1)//right
			return 1!=maze[mouseX][mouseY+1]&&maze[mouseX][mouseY+1]!=2;
		else if (mouseDirection==2)//down
			return 1!=maze[mouseX-1][mouseY]&&maze[mouseX-1][mouseY]!=2;
		else//left
			return 1!=maze[mouseX][mouseY-1]&&maze[mouseX][mouseY-1]!=2;
	}

	public boolean isFinished () {
		return maze[mouseX][mouseY]==3;
	}

	public void resetMouse () {
		stepCounter=0;
		mouseDirection=0;
		mouseX=-1;
		mouseY=-1;
	}

	public void printMaze () {
		System.out.print ("Direction: ");
		if (mouseDirection==0)
			System.out.println ("up");
		else if (mouseDirection==1)
			System.out.println ("right");
		else if (mouseDirection==2)
			System.out.println ("down");
		else
			System.out.println ("left");

		for (int y=0;y<10;y++) {
			for (int x=0;x<10;x++) {
				if (x==mouseX&&mouseY==y)
					System.out.print('*');
				else
					System.out.print (maze[x][y]);
			}
			System.out.println();
		}
		System.out.println("\n");
	}

	public Simulator  () throws Exception{
		double totalStepsCountRandom=0, averageStepsCount=0,totalStepsCountRight=0;
		final int NUM_TEST_MAZES=5;
		System.out.println ("\nBegining testing with always right logic");
		for (int x=0;x<NUM_TEST_MAZES;x++) {
			System.out.println ("\nLoading Maze "+x);
			resetMouse();
			loadMaze(new File("Mazes/maze"+x));
			alwaysRightLogic ();
			totalStepsCountRight+=stepCounter;
			System.out.println ("Steps Taken Counter using always right logic is: "+stepCounter);

			resetMouse();
			loadMaze(new File("Mazes/maze"+x));
			randomLogic ();
			totalStepsCountRandom+=stepCounter;
			System.out.println ("Steps Taken Counter using random logic is: "+stepCounter);	
		}
		System.out.println ("Average amount of steps to solve a maze with always right reasoning was: "+(totalStepsCountRight+0.0)/NUM_TEST_MAZES);
		System.out.println ("Average amount of steps to solve a maze with random reasoning was: "+(totalStepsCountRandom+0.0)/NUM_TEST_MAZES);
	}

	public static void main (String[] args) throws Exception{
		new Simulator ();
	}
}