/* Pin Map:
Digital:
0 - Avoid if possible. Serial output
1 - Avoid if possible. Serial output
2 - Red LED
3 - Yellow LED
4 - Green LED
5 - Calibration button
6 - Motor AF - Left motor forward
7 - Motor AB - left motor backward
8 - Motor BF - right motor forward
9 - Motor BB - right motor backward
10 - Bright LED? Gets turned off if Mouse is using Ultrasonic instead
11 - Empty
12 - Empty
13 - Empty
Anlog:
A0 - LDR or Ultrasonic **LDR's are (Left to Right)**
A1 - LDR or Ultrasonic
A2 - LDR
A3 - LDR
A4 - LDR
A5 - Empty


CAR LAYOUT
0,1,2,3,4,-LDR at Array Value
W-Wheel

***FRONT***
+++++++++++
+*********+
+*********+
+*********+
+0**123**4+
+WW*****WW+
+*********+
+*********+
+*********+
+*********+
+++++++++++
*/

const int redLED = 2; //LED pin indicating: Press button to set white values
const int yellowLED = 3; //LED pin indicating: Press button to set black values
const int greenLED = 4; //LED pin indicating: Press button to go
const int button = 5; //Digital input for calibration button
int white [5]; //Value saved on white button press
int black [5]; //Value saved on black button press
int threshold [5]; //Average between white and black.
boolean ldr [5]; //1 if over black, 0 otherwise
const int motorAF = 6; //Motor A forward pin
const int motorAB = 7; //Motor A backward pin
const int motorBF = 8; //Motor B forward pin
const int morotBB = 9; //Motor B backward pin
const int smallDelayValue=300; //Delay length for different movement related stuff

void setup(){
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(button, INPUT);
  pinMode(motorAF, OUTPUT);
  pinMode(motorAB, OUTPUT);
  pinMode(motorBF, OUTPUT);
  pinMode(motorBB, OUTPUT);
  readWhite();
  readBlack();
  setThresholds();
  digitalWrite(greenLED, HIGH);
  while(digitalRead(button)!=HIGH){}
  loop();
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
  digitalWrite(yellowLED, HIGH);
  while(digitalRead(button) != HIGH){}
  for (int i = 0; i<5; i++){
    black[i] = analogRead(i);
  }
  while(digitalRead(button) == HIGH){}
  digitalWrite(yellowLED, LOW);
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
  digitalWrite(motorAF, 0);
  digitalWrite(motorAB, 0);
  digitalWrite(motorBF, 0);
  digitalWrite(motorBB, 0);
}

void forward(){
  halt();
  digitalWrite(motorAF, 1);
  digitalWrite(motorBF, 1);
}

void backward() {
  halt();
  digitalWrite(motorAB, 1);
  digitalWrite(motorBB, 1);
}

void right(){
  halt();
  digitalWrite(motorAF, 1);
  digitalWrite(motorBB, 1);
}

void left(){
  halt();
  digitalWrite(motorAB, 1);
  digitalWrite(motorBF, 1);
}

//Assuming we started with WBBBB (LDR Values) when called
void turnRight () {
  right(); //Start turning 
  delay (smallDelayValue); //Give time to start turning
  while (true) { //Now we assume WWBWW (LDR Values)
    updateLDRValues();
    if (ldr[4]&&ldr[3]&&ldr[2]&&ldr[1]) { //If all four evaluate to true, then it means WBBBB
      halts();
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
    if (ldr[1]&&ldr[2]&&ldr[3]) {
      halt();
      break;
    }
  }
  reverseDirection();//turn Around
}

//Assuming WBBBW
void reverseDirection () {
  right();
  while (true){
    updateLDRValues ()
    if (ldr[0]&&ldr[1]&&ldr[2]&&ldr[4]&&ldr[3]) { //Means mouse s prendicular
      delay (smallDelayValue);//Let the mouse keep turning for a bit
      halt();
      break;//Won't know if perfectly straight, but adjust functions should fix that
    }
}

}

void adjustRight () {

}

void adjustLeft () {

}

boolean isFinished () {//This overlaps with T intersection? Add Random LDR in special location that never gets thrown?
  return ldr[0]&&ldr[1]&&ldr[3]&&ldr[4]&&ldr[2];
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
    switch (true) {
      case ldr[4]:
        turnRight();
        forward();
        delay(smallDelayValue);
        break;
      case ldr[0]:
        turnLeft();
        forward();
        delay (smallDelayValue);
        break;
      case ldr[2]&&ldr[3]:
        adjustLeft();
        break;
      case ldr[1]&&ldr[2]:
        adjustRight();
        break;
      case !ldr[0]&&!ldr[1]&&!ldr[2]&&!ldr[4]&&!ldr[3]:
        goneTooFar();
        delay(smallDelayValue);
        break;
      default:
        forward();
    }
  }
}