public class RandomMouse extends Mouse {
  
  public RandomMouse (Simulator sim)
  {
    super(sim);
  }
  public RandomMouse (int xCoord, int yCoord, int direction, Simulator sim) {
    super (xCoord, yCoord,  direction, sim);
  }
  
  @Override
  public void logic () {
    double r;
    while (!getSim().isFinished(this)) {
      if (getSim().rightOpen(this)&&getSim().forwardOpen(this)&&getSim().leftOpen(this)) {
        r=Math.random();
        if (r<0.3)
          turnLeft();
        else {
          if (r<0.6) 
            turnRight();
        }
        goForward();
      } 
      else if (getSim().forwardOpen(this)&&getSim().leftOpen(this)) {
        r=Math.random();
        if (r<0.5)
          turnLeft();
        goForward();
      }
      else if (getSim().rightOpen(this)&&getSim().forwardOpen(this)) {
        r=Math.random();
        if (r<0.5)
          turnRight();
        goForward();
      }
      else if (getSim().rightOpen(this)&&getSim().leftOpen(this)) {
        r=Math.random();
        if (r<0.5)
          turnRight();
        else
          turnLeft();
        goForward();
      }
      else if (getSim().leftOpen(this)) {
        turnLeft();
        goForward();
      }
      else if (getSim().rightOpen(this)) {
        turnRight();
        goForward();
      }
      else if (getSim().forwardOpen(this)) {
        goForward();
      }
      else { //Dead End
        turnRight();
        turnRight();
        goForward();
      }
    }
  }
}