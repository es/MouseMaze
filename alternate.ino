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
+0**123**4+
+*********+
+*********+
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
boolean isFinished = false;

const int motorAF = 6; //Motor A forward pin
const int motorAB = 7; //Motor A backward pin
const int motorBF = 8; //Motor B forward pin
const int motorBB = 9; //Motor B backward pin
const int smallDelayValue=300; //Delay length for different movement related stuff

void setup(){
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(redLED, HIGH);
  while(digitalRead(button)!=HIGH){} //Position the LDRs over white and hit button
  readWhite();
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, HIGH);
  while(digitalRead(button)!=HIGH){} //Position the LDRs over black and hit button
  readBlack();
  setThresholds();
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, HIGH);
  while(digitalRead(button)!=HIGH){} //Position the car at the start and hit button
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
  analogWrite(motorAF, 0);
  analogWrite(motorAB, 0);
  analogWrite(motorBF, 0);
  analogWrite(motorBB, 0);
}

void forward(){
  halt();
  analogWrite(motorAF, 1023);
  analogWrite(motorBF, 1023);
}

void backward() {
  halt();
  analogWrite(motorAB, 1023);
  analogWrite(motorBB, 1023);
}

void right(){
  halt();
  analogWrite(motorAF, 1023);
  analogWrite(motorBB, 1023);
}

void left(){
  halt();
  analogWrite(motorAB, 1023);
  analogWrite(motorBF, 1023);
}

//Turn right until middle LDR finds black.
void turnRight () {
  right(); //Start turning 
  delay (smallDelayValue);
  while (true) {
    updateLDRValues();
    if (ldr[2]) {
      forward();
      break;
    }
  }
}

//Turn left until middle LDR finds black
void turnLeft () {
  left(); //Start turning 
  delay (smallDelayValue); //Give time to start turning
  while (true) {
    updateLDRValues();
    if (ldr[2]) {
      forward();
      break;
    }
  }
}


void adjustRight () {
  analogWrite(motorAF, 1023);
  analogWrite(motorBF, 723);
}

void adjustLeft () {
  analogWrite(motorAF, 723);
  analogWrite(motorBF, 1023);
}

//The mouse has been notified that it has hit an intersection. Identify and act upon which type it is.
void identifyIntersection(){
  boolean b[3] = {ldr[0], ldr[1]|ldr[2]|ldr[3], ldr[4]}; //Before intersection
  forward();
  delay(smallDelayValue);
  halt();
  updateLDRValues();
  boolean a[3] = {ldr[0], ldr[1]|ldr[2]|ldr[3], ldr[4]}; //After intersection  
  if (b[0]&&b[1]&&b[2]){ //T, Cross, or End        
    if (!(a[0] || a[2])) //T or Cross
      turnRight();
    else
      isFinished = true;
  }
  else if (b[0]){ //Right turn or right T
    turnRight();
  }
  else{ //Left turn or left T
     turnLeft();
  }
}

//Detect a requirement to do either a 90 or 180 degree turn
void detectTurn(){
  updateLDRValues();
  if (!(ldr[1] || ldr[2] || ldr[3])) //Dead end
    turnRight();
  if (ldr[0] || ldr[4]){ //Either an intersection or the ending
    halt();
    identifyIntersection();
  }
}

//Detect a requirement to adjust direction
void detectAdjust(){
  updateLDRValues();
  if (ldr[1] && ldr[2] && !ldr[3])
   adjustRight();
  else if (!ldr[1] && ldr[2] && ldr[3])
   adjustLeft();
  else
    forward();
}

void loop () {
  if (!isFinished){
    detectTurn();
    detectAdjust();
  }
}
