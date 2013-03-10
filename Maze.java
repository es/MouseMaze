//Maze.java
import javax.swing.*;
import java.awt.*;

public class Maze extends JPanel {
	
	public Maze () {
		super();
		this.setSize (300,300);
		this.setBackground(Color.black);
		this.setVisible (true);
	}

	public void setup () {
		for (int x=0;x<100;x++) {
			this.setLocation (200-x,200-x);
		}
	}

	public void generateMaze () {}

	public void addMouse () {}

	//public void update (Graphics g) {}

	
}