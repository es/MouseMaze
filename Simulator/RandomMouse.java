public class RandomMouse extends Mouse {
  public RandomMouse (int xCoord, int yCoord, int direction, Simulator sim) {
    super (xCoord, yCoord,  direction, sim);
  }
  
  @Override
  public void logic () {
    double r;
    while (!getSim().isFinished(getX(),getY())) {
      if (getSim().rightOpen(getX(), getY(), getDirection())&&getSim().forwardOpen(getX(), getY(), getDirection())&&getSim().leftOpen(getX(), getY(), getDirection())) {
        r=Math.random();
        if (r<0.3)
          turnLeft();
        else {
          if (r<0.6) 
            turnRight();
        }
        goForward();
      } 
      else if (getSim().forwardOpen(getX(), getY(), getDirection())&&getSim().leftOpen(getX(), getY(), getDirection())) {
        r=Math.random();
        if (r<0.5)
          turnLeft();
        goForward();
      }
      else if (getSim().rightOpen(getX(), getY(), getDirection())&&getSim().forwardOpen(getX(), getY(), getDirection())) {
        r=Math.random();
        if (r<0.5)
          turnRight();
        goForward();
      }
      else if (getSim().rightOpen(getX(), getY(), getDirection())&&getSim().leftOpen(getX(), getY(), getDirection())) {
        r=Math.random();
        if (r<0.5)
          turnRight();
        else
          turnLeft();
        goForward();
      }
      else if (getSim().leftOpen(getX(), getY(), getDirection())) {
        turnLeft();
        goForward();
      }
      else if (getSim().rightOpen(getX(), getY(), getDirection())) {
        turnRight();
        goForward();
      }
      else if (getSim().forwardOpen(getX(), getY(), getDirection())) {
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