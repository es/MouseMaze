/* Pin Map:
* - PWM Pin
Digital:
0 - Avoid if possible. Serial output 
1 - Avoid if possible. Serial output
2 - LDR<-->Ultrasonic Switch, Always Starts with LDR
3*- Front Ultrasonic Pin for Echo Call
4 - Right Ultrasonic Trigger Pin
5*- Right Ultrasonic Pin for Echo Call
6*- Motor AF - Left motor forward
7 - Bright LED? Gets turned off if Mouse is using Ultrasonic instead
8 - Red LED
9*- Motor AB - left motor backward
10*- Motor BF - right motor forward
11*- Motor BB - right motor backward
12 - Front Ultrasonic Trigger Pin
13 - Green LED  
Anlog:
A0 - LDR
A1 - LDR
A2 - LDR
A3 - LDR
A4 - LDR
A5 - Calibration button


CAR LAYOUT
0,1,2,3,4,-LDR at Array Value
W-Wheel

***FRONT***
+++++++++++
+*********+
+*********+
+*********+
+0**123**4+
+AW*****WB+
+*********+
+*********+
+*********+
+*********+
+++++++++++
*/

//Ultrasonic Declarations
#include <NewPing.h>
const int sonicFrontEcho=3; //Pin tied to echo pin on the front ultrasonic sensor.
const int sonicFrontTriggerPin=12; //Pin tied to trigger pin on the front ultrasonic sensor.
const int sonicRightEcho=5; //Pin tied to echo pin on the right ultrasonic sensor.
const int sonicRightTriggerPin=4; //Pin tied to trigger pin on the right ultrasonic sensor.
const int sonicMaxDistance=100; //Maximum distance (in centimeters)
const int widthOfMaze=20; //Width of maze in cm, should be constant
unsigned int distanceRight; //Distance to the right of the mouse (in cm)
unsigned int distanceFront; //Distance infront of Mouse (in cm)
NewPing frontSonar (sonicFrontTriggerPin,sonicFrontEcho,sonicMaxDistance); //Front NewPing setup
NewPing rightSonar (sonicRightTriggerPin,sonicRightEcho,sonicMaxDistance); //Right NewPing setup

//Motor Declarations
const int motorAF = 6; //Motor A forward pin
const int motorAB = 9; //Motor A backward pin
const int motorBF = 10; //Motor B forward pin
const int motorBB = 11; //Motor B backward pin
const int maxSpeed=1023; //Fast Motor Speed
const int mediumSpeed=768; //Medium Motor Speed
const int slowSpeed=512; //Slow Motor Speed
int currentSpeed; //Speed at which motors should be turning at any moment in time, unless adjusting speed

//General Declarations
const int redLED = 8; //LED pin indicating: Press button to set white values
const int greenLED = 13; //LED pin indicating: Press button to go
const int button = A5; //Digital input for calibration button
int white [5]; //Value saved on white button press
int black [5]; //Value saved on black button press
int threshold [5]; //Average between white and black.
boolean ldr [5]; //1 if over black, 0 otherwise
const int smallDelayValue=300; //Delay length for different movement related stuff
unsigned long start_time = -1; //start time when all ldrs are black. Unsigned since we're dealing with time.
const int stop_thresh = 3000; //If time passed reaches this value, maze solved.
boolean ldrForNavigation=true;

void setup(){
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(button, INPUT);
  pinMode(motorAF, OUTPUT);
  pinMode(motorAB, OUTPUT);
  pinMode(motorBF, OUTPUT);
  pinMode(motorBB, OUTPUT);
  readWhite();
  readBlack();
  currentSpeed=maxSpeed;
  setThresholds();
  attachInterrupt (0, changeNavMethod, CHANGE);
  digitalWrite(greenLED, HIGH);
  while(digitalRead(button)!=HIGH){}
  loop();
}

//Called on when switch is flipped for LDR<-->Ultrasonic
void changeNavMethod () {
  halt();
  ldrForNavigation=!ldrForNavigation;
  if (ldrForNavigation) 
    currentSpeed=maxSpeed;
  else
    currentSpeed=slowSpeed; //Ultrasonic needs to move slower so it has time to update
}

void readWhite(){
  digitalWrite(redLED, HIGH);
  while(digitalRead(button) != HIGH){}
    for (int i = 0; i<5; i++){
      white[i] += analogRead(i);
    }
    while(digitalRead(button) == HIGH){}
      digitalWrite(redLED, LOW);
  }

  void readBlack(){
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, HIGH);
    while(digitalRead(button) != HIGH){}
      for (int i = 0; i<5; i++){
        black[i] = analogRead(i);
      }
      while(digitalRead(button) == HIGH){}
        digitalWrite(redLED, LOW);
    }

    void setThresholds(){
      for (int i = 0; i<5; i++){
        threshold[i] = (white[i]+black[i])/2;
      }
    }

    void updateLDRValues(){
      for (int i = 0; i<5; i++){
        if (analogRead(i)<threshold[i])
      ldr[i]=0; //Black
    else
      ldr[i]=1; //White
  }
}

void halt(){
  analogWrite(motorAF, 0);
  analogWrite(motorAB, 0);
  analogWrite(motorBF, 0);
  analogWrite(motorBB, 0);
}

void forward(){
  halt();
  analogWrite(motorAF, currentSpeed);
  analogWrite(motorBF, currentSpeed);
}

void backward() {
  halt();
  analogWrite(motorAB, currentSpeed);
  analogWrite(motorBB, currentSpeed);
}

void right(){
  halt();
  analogWrite(motorAF, currentSpeed);
  analogWrite(motorBB, currentSpeed);
}

void left(){
  halt();
  analogWrite(motorAB, currentSpeed);
  analogWrite(motorBF, currentSpeed);
}

//Assuming we started with WBBBB (LDR Values) when called
void turnRight () {
  right(); //Start turning 
  delay (smallDelayValue); //Give time to start turning
  while (true) { //Now we assume WWBWW (LDR Values)
    updateLDRValues();
    if (ldr[4]&&(ldr[3]+ldr[2]+ldr[1])>=2) { //If all four evaluate to true, then it means WBBBB
      halt();
      break;
    }
  }
}

//Assuming we started with BBBWW (LDR Values) when called
void turnLeft () {
  left(); //Start turning 
  delay (smallDelayValue); //Give time to start turning
  while (true) { //Now we assume WWBWW (LDR Values)
    updateLDRValues();
    if (ldr[0]&&ldr[1]&&ldr[2]&&ldr[3]) { //If all four evaluate to true, then it means BBBWW
      halt();
      break;
    }
  }
}

//Called when run off path by going forward for too long
//Assuming WWWWW
void goneTooFar () {
  backward();
  while (true) {
    updateLDRValues ();
    if ((ldr[1]+ldr[2]+ldr[3])>=2) {
      halt();
      break;
    }
  }
  forward();
  delay(smallDelayValue);
  halt();
  left();
  while (!(ldr[1]+ldr[2]+ldr[3])>=2) {};
  halt();
}

//Assuming WBBBW
void reverseDirection () {
  right();
  while (true){
    updateLDRValues ();
    if (ldr[0]&&ldr[1]&&ldr[2]&&ldr[4]&&ldr[3]) { //Means mouse s prendicular
      delay (smallDelayValue);//Let the mouse keep turning for a bit
      halt();
      break;//Won't know if perfectly straight, but adjust functions should fix that
    }
  }

}

void adjustRight () {
	analogWrite(motorAF, currentSpeed);
  analogWrite(motorBF, currentSpeed/2);
}

void adjustLeft () {
  analogWrite(motorAF, currentSpeed/2);
  analogWrite(motorBF, currentSpeed);
}

boolean isFinished () {//Approach to figuring out the LDR logic for if the maze has been completed or not.

  if (ldr[0]&&ldr[1]&&ldr[3]&&ldr[4]&&ldr[2]){

    if (start_time == -1){
      start_time = millis();//all LDRs on black and this is a first time thing, so set start_time to the current time
    }

    if (millis() - start_time >= stop_thresh){ //check to see how long we've been on black for and if it's been enough, we're done!
      return true;
  }

}
else {
  start_time = -1;//LDR(s) are white, so no point in keeping track of time. Reset this variable.
}
return false;
}

void updateUltrasonicValues () {
  distanceFront=frontSonar.convert_cm(frontSonar.ping_median());
  distanceRight=rightSonar.convert_cm(rightSonar.ping_median());
}

void dance () {
  //IT'S PARTY TIME!!!
  int currentTime;
  currentSpeed=maxSpeed;
  boolean iShouldTurnRight=true;
  while (true) {
    currentTime=millis();
    while (millis()-currentTime<=3000) {
      if (iShouldTurnRight)
        right();
      else
        left();
    }
    iShouldTurnRight=!iShouldTurnRight;
  }
}

/*Values of LDR's and Intersection Type
ldr[0]&&ldr[1]&&ldr[2]&&ldr[4]&&ldr[3]=True, Either T or 4-Way Intersection <---Turns out this is redundant cause we still just a turn right :D
ldr[0]=True, Left Turn
ldr[4]=True, Right Turn
ldr[1]&&ldr[2]=True, Adjust right
ldr[2]&&ldr[3]=True, Adjust left
*/
void loop () {
  while (!isFinished()) {
    if (ldrForNavigation) {
      if (ldr[4]) {
        turnRight();
        forward();
        delay(smallDelayValue);
      }
      else if (ldr[2]&&ldr[3]) {
        adjustLeft();
      }
      else if (ldr[1]&&ldr[2]) {
        adjustRight();
      }
      else if (!ldr[0]&&!ldr[1]&&!ldr[2]&&!ldr[4]&&!ldr[3]) {
        goneTooFar();
        forward();
        delay(smallDelayValue);
      }
      else {
        forward();
      }
    }
    else { //Logic of mouse if Using Ultrasound
      updateUltrasonicValues();
      if (distanceRight>widthOfMaze) {//If distance to the right is greater than 20cm, Turn Right
        halt();
        currentSpeed=slowSpeed;
        right();
        //The while loop is constantly checking the distance of the front sonar, if it matches the distance of the original right
        //sonar when the turn started then it has completed the turn. Note: The match is to 3cm accuracy cause we love hearts!
        while (!abs(distanceRight-frontSonar.convert_cm(frontSonar.ping_median()))<3) {} //A HEART, SOMEBODY MUST LOVE ME<3
        halt();
        currentSpeed=mediumSpeed;
        forward();
        //TurnRight
      }
      else if (distanceFront>widthOfMaze/2) {//If the distance in front of the car is less than half, turn left.
        halt();
        currentSpeed=slowSpeed;
        left();
        //Same logic as while loop above only this time it is checking the current distance of the right sonar compared to the 
        //original front distance.
        while (!abs(distanceFront-rightSonar.convert_cm(rightSonar.ping_median()))<3) {} //COULD IT POSSIBLY BE ANOTHER HEART?!
        halt();
        currentSpeed=mediumSpeed;
      }
      else if (distanceRight<widthOfMaze/2) {//Adjust check
        adjustLeft();
      }
      else if (distanceRight>widthOfMaze/2) {//Adjust check
        adjustRight();
      }
      else {
        forward();
      }
    }
  }
  dance ();
}
