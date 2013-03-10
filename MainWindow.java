//MainWindow.java
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.*;

public class MainWindow extends JFrame implements ActionListener {
	Maze maze;

	public MainWindow () {
		super ();
		this.setTitle ("Mouse Traversing Maze Simulator");
		this.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);
		this.setSize (500,500);
		
		//BorderLayout layout = new BorderLayout (0,0);
		this.setLayout (null);

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

		//this.setResizable(false);
		this.setVisible (true);
		addMaze();
	}

	public void addMaze () {
		Maze maze= new Maze ();
		this.getContentPane().setSize(500,500);
		System.out.println(this.getContentPane().getSize());
		this.add(maze, BorderLayout.CENTER);
		maze.setup();
		//this.update();
	}

	public void actionPerformed(ActionEvent ae) {
        if (ae.getActionCommand().equals("exit")) {
          	System.exit (0);
        }
    }
}