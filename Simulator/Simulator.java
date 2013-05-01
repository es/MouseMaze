import java.util.*;
import java.io.*;

public class Simulator {
  private int maze[][]=new int [10][10];//0=open, 1=closed, 2=start, 3=finished
  private int stepCounter;
  private List<Mouse> mouseList=new ArrayList<Mouse> ();
  private int startX;
  private int startY;
  private int startDirection;
  
  private int [] stepCounters = {0,0,0};
  
  public void move (int x, int y){
    if (maze[x][y]!=1)
      stepCounter++;
    else
      throw new RuntimeException ("On a 1 value!");
  }
  
  public void loadMaze (File document) throws Exception {
    startX = -1;
    startY = -1;
    
    try {
      BufferedReader in=new BufferedReader (new FileReader(document.toString()));
      for (int y=0;y<10;y++) {
        String s=in.readLine().trim();
        
        int startLocation = s.indexOf ("2");
        
        if (startLocation != -1){
          if(y == 0)
            startDirection = Mouse.DIRECTION_DOWN;
          else if (y == 10)
            startDirection = Mouse.DIRECTION_UP;
          else if (startLocation == 0)
            startDirection = Mouse.DIRECTION_RIGHT;
          else if (startLocation == s.length()-1)
            startDirection = Mouse.DIRECTION_LEFT;
          
          startX = startLocation;
          startY = y;
        }
        
        char[] temp=s.toCharArray();
        for (int x=0;x<10;x++){
          maze[x][y]=Integer.parseInt(String.valueOf(temp[x]));
        }
      }
    }
    catch (IOException woops) {
      woops.printStackTrace (System.out);
    }
    
    if (startX == -1 && startY == -1)
      throw new RuntimeException ("Coordinates are -1");
  }
  
  public boolean forwardOpen (Mouse m) {
    if (m.getDirection()==Mouse.DIRECTION_UP)//up
      return 1!=maze[m.getX()][m.getY()-1]&&maze[m.getX()][m.getY()-1]!=2;
    else if (m.getDirection()==Mouse.DIRECTION_RIGHT)//right
      return 1!=maze[m.getX()+1][m.getY()]&&maze[m.getX()+1][m.getY()]!=2;
    else if (m.getDirection()==Mouse.DIRECTION_DOWN)//down
      return 1!=maze[m.getX()][m.getY()+1]&&maze[m.getX()][m.getY()+1]!=2;
    else//left
      return 1!=maze[m.getX()-1][m.getY()]&&maze[m.getX()-1][m.getY()]!=2;
  }
  
  public boolean backwardOpen (Mouse m) {
    if (m.getDirection()==Mouse.DIRECTION_UP)//up
      return 1!=maze[m.getX()][m.getY()+1]&&maze[m.getX()][m.getY()+1]!=2;
    else if (m.getDirection()==Mouse.DIRECTION_RIGHT)//right
      return 1!=maze[m.getX()-1][m.getY()]&&maze[m.getX()-1][m.getY()]!=2;
    else if (m.getDirection()==Mouse.DIRECTION_DOWN)//down
      return 1!=maze[m.getX()][m.getY()-1]&&maze[m.getX()][m.getY()-1]!=2;
    else//left
      return 1!=maze[m.getX()+1][m.getY()]&&maze[m.getX()+1][m.getY()]!=2;
  }
  
  public boolean leftOpen (Mouse m) {
    if (m.getDirection()==Mouse.DIRECTION_UP)//up
      return 1!=maze[m.getX()-1][m.getY()]&&maze[m.getX()-1][m.getY()]!=2;
    else if (m.getDirection()==Mouse.DIRECTION_RIGHT)//right
      return 1!=maze[m.getX()][m.getY()-1]&&maze[m.getX()][m.getY()-1]!=2;
    else if (m.getDirection()==Mouse.DIRECTION_DOWN)//down
      return 1!=maze[m.getX()+1][m.getY()]&&maze[m.getX()+1][m.getY()]!=2;
    else//left
      return 1!=maze[m.getX()][m.getY()+1]&&maze[m.getX()][m.getY()+1]!=2;
  }
  
  public boolean rightOpen (Mouse m) {
    if (m.getDirection()==Mouse.DIRECTION_UP)//up
      return 1!=maze[m.getX()+1][m.getY()]&&maze[m.getX()+1][m.getY()]!=2;
    else if (m.getDirection()==Mouse.DIRECTION_RIGHT)//right
      return 1!=maze[m.getX()][m.getY()+1]&&maze[m.getX()][m.getY()+1]!=2;
    else if (m.getDirection()==Mouse.DIRECTION_DOWN)//down
      return 1!=maze[m.getX()-1][m.getY()]&&maze[m.getX()-1][m.getY()]!=2;
    else//left
      return 1!=maze[m.getX()][m.getY()-1]&&maze[m.getX()][m.getY()-1]!=2;
  }
  
  public void addMouse (Mouse newMouse) {
    mouseList.add(newMouse);
  }
  
  public boolean isFinished (Mouse m) {
    return maze[m.getX()][m.getY()]==3;
  }
  
  public void resetMouse (Mouse m) {
    stepCounter=0;
    m.reset (startX, startY, startDirection);
  }
  
  public void incrementCounter (Mouse m, int amount){
    stepCounters [m.getLogicType()] += amount;
  }
  
  public void simulate () throws Exception {
    double totalStepsCountRandom=0, averageStepsCount=0,totalStepsCountRight=0;
    final int NUM_TEST_MAZES=5;
    for (int x=0;x<NUM_TEST_MAZES;x++) {
      System.out.println ("\nLoading Maze "+x);
      loadMaze(new File("Mazes/maze"+x));
      
      for (Mouse m:mouseList){
        resetMouse(m);
        m.logic();
        incrementCounter(m,stepCounter);
        System.out.println ("Steps Taken Counter using " + m.getLogicName() + " logic is: "+stepCounter);
      }
    }
    
    System.out.println ();
    
    for (int x =0; x <stepCounters.length;x++){
      System.out.println ("Average amount of steps to solve a maze with " + (x == Mouse.ALWAYS_RIGHT_LOGIC ? "always right logic ": "random logic " )
                            +(stepCounters[x]+0.0)/NUM_TEST_MAZES);
    }    
  }
  
  public static void main (String[] args) throws Exception{
    Simulator sim=new Simulator ();
    sim.addMouse(new RandomMouse(sim));
    sim.addMouse(new AlwaysRightMouse(sim));
    sim.addMouse(new LearningRandomMouse(sim));
    sim.simulate();
    
    
  }
}