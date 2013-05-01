public class LearningRandomMouse extends Mouse {
  
  public LearningRandomMouse (Simulator sim)
  {
    super(sim);
  }
  public LearningRandomMouse (int xCoord, int yCoord, int direction, Simulator sim) {
    super (xCoord, yCoord,  direction, sim);
  }
  
  @Override
  public void logic () {
    
  }
  
  @Override
  public int getLogicType ()
  {
    return LEARNING_RANDOM_LOGIC;
  }
}