public class AlwaysRightMouse extends Mouse {
  
 public AlwaysRightMouse (int mouseX, int mouseY, int mouseDirection, Simulator sim) {
    super(mouseX, mouseY, mouseDirection,sim);
 }

 @Override
 public void logic ()  {
  while (!getSim().isFinished(getX(), getY())) {
   if (getSim().rightOpen(getX(), getY(), getDirection())) {
    turnRight();
    goForward();
   } 
   else if (!getSim().forwardOpen(getX(), getY(), getDirection()))
    turnLeft();
   else
    goForward();
   //printMaze();
  }
 }
 
}