public class AlwaysRightMouse extends Mouse {
  
  public AlwaysRightMouse (Simulator sim)
  {
    super(sim);
  }
  public AlwaysRightMouse (int mouseX, int mouseY, int mouseDirection, Simulator sim) {
    super(mouseX, mouseY, mouseDirection,sim);
  }
  
  @Override
  public void logic ()  {
    while (!getSim().isFinished(this)) {
      if (getSim().rightOpen(this)) {
        turnRight();
        goForward();
      } 
      else if (!getSim().forwardOpen(this))
        turnLeft();
      else
        goForward();
    }
  }
}