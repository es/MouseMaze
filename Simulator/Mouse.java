public abstract class Mouse {
  private int xCoord;
  private int yCoord;
  private int direction;//0=Up, 1=Right, 2=Down, 3=Left
  private Simulator sim;
  
  public static final int DIRECTION_UP = 0;
  public static final int DIRECTION_RIGHT = 1;
  public static final int DIRECTION_DOWN = 2;
  public static final int DIRECTION_LEFT = 3;
  
  public static final int ALWAYS_RIGHT_LOGIC = 0;
  public static final int RANDOM_LOGIC = 1;
  
  public Mouse (Simulator sim)
  {
    reset (0,0,0);
    this.sim = sim;
  }
  public Mouse (int xCoord, int yCoord, int direction, Simulator sim) {
    reset (xCoord,yCoord,direction);
    this.sim=sim;
  }
  
  public void reset(int xCoord, int yCoord, int direction)
  {
    this.xCoord = xCoord;
    this.yCoord = yCoord;  
    this.direction = direction;
  }
  
  public int getX()
  {
    return xCoord;
  }
  
  public int getY()
  {
    return yCoord;
  }
  
  public int getDirection()
  {
    return direction;
  }
  
  public Simulator getSim()
  {
    return sim;
  }
  
  abstract void logic ();
  
  public void goForward (){
    if (direction==DIRECTION_UP) //up
      yCoord--;
    else if (direction==DIRECTION_RIGHT) //right
      xCoord++;
    else if (direction==DIRECTION_DOWN) //down
      yCoord++;
    else //left
      xCoord--;
      sim.move(xCoord,yCoord);
  }
  
  public void turnRight () {
    if (direction==DIRECTION_LEFT)
      direction=DIRECTION_UP;
    else
      direction++;
  }
  
  public void turnLeft () {
    if (direction==DIRECTION_UP)
      direction=DIRECTION_LEFT;
    else
      direction--;
  } 
  
  public String toString (){
    return String.format ("X-coord: %d\nY-coord: %d\nDirection: %d",xCoord,yCoord,direction);
  }
  
  public String getLogicName ()
  {
    return this.getClass().getName();
  }
  
  public abstract int getLogicType();
}