//MouseMaze.java
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.*;

public class MouseMaze extends JFrame implements ActionListener {
	
	public MouseMaze () {
		super ();
		this.setTitle ("Mouse Traversing Maze Simulator");
		this.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);
		this.setSize (500,500);
		this.setResizable(false);
		BorderLayout layout = new BorderLayout (0,0);
		this.setLayout (layout);

		JMenuBar menuBar= new JMenuBar ();
		JMenu file = new JMenu ("File");

		JMenuItem newMaze = new JMenuItem ("New Maze");
		newMaze.setActionCommand ("newMaze");
		newMaze.addActionListener(this);
		file.add(newMaze);

		JMenuItem exit = new JMenuItem ("Exit");
		exit.setActionCommand("exit");
		exit.addActionListener(this);
		file.add(exit);

		menuBar.add (file);
		this.setJMenuBar (menuBar);

		this.setVisible (true);
	}

	public void actionPerformed(ActionEvent ae) {
        if (ae.getActionCommand().equals("exit")) {
          	System.exit (0);
        }
    }

	public static void main (String [] args) {
		new MouseMaze();
	}
}