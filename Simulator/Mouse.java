public abstract class Mouse {
  private int xCoord;
  private int yCoord;
  private int direction;//0=Up, 1=Right, 2=Down, 3=Left
  private Simulator sim;
  
  public Mouse (int xCoord, int yCoord, int direction, Simulator sim) {
    this.xCoord=xCoord;
    this.yCoord=yCoord;
    this.direction=direction;
    this.sim=sim;
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
    if (direction==0) //up
      yCoord--;
    else if (direction==1) //right
      xCoord++;
    else if (direction==2) //down
      yCoord++;
    else //left
      xCoord--;
    try{
      sim.move(xCoord,yCoord);
    }
    catch (Exception e)
    {
      e.printStackTrace();
    }
  }
  
  public void turnRight () {
    if (direction==3)
      direction=0;
    else
      direction++;
  }
  
  public void turnLeft () {
    if (direction==0)
      direction=3;
    else
      direction--;
  } 
  
  public String toString (){
    return String.format ("X-coord: %d\nY-coord: %d\nDirection: %d",xCoord,yCoord,direction);
  }
  

 public String getLogicType ()
 {
   return this.getClass().getName();
 }
 

}