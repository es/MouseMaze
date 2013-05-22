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
boolean ldr [5]; //1 if over black, 0 otherwise; ldr[0] is rightest, ldr[4] is leftest
boolean isFinished = false;

const int motorAF = 6; //Motor A forward pin
const int motorAB = 9; //Motor A backward pin
const int motorBF = 10; //Motor B forward pin
const int motorBB = 11; //Motor B backward pin
const int smallDelayValue=300; //Delay length for different movement related stuff
int currentSpeed=915;//850 slowest
int LDRValue=0;

void setup () {
  Serial.begin(9600);
  Serial.println("NEW CODE!");
Serial.println("Turn on white light");
pinMode(13,OUTPUT);
digitalWrite(13,HIGH);
//testWheeles();
readWhite();
readBlack();
setThresholds();
}

void countDown(int a) {
  for (int x=a;x>0;x--) {
    Serial.println(x);
    delay(1000);
  }
}

void testWheeles() {
  halt();
  Serial.println ("Forward Test");
  countDown(5);
  forward();
  countDown(5);
  Serial.println("HALT!");
  halt();
  delay(3000);
  
  halt();
  Serial.println ("Forward Test");
  countDown(5);
  for (int x=0;x<173;x++) {
    currentSpeed=1023-x;
    Serial.println(currentSpeed);
    forward();
    delay(125);
  }
  
  halt();
  Serial.println ("Backward Test");
    countDown(5); 
  for (int x=0;x<173;x++) {
    currentSpeed=1023-x;
    Serial.println(currentSpeed);
    backward();
    delay(125);
  }
  
  halt();
  Serial.println ("Left Test");
  countDown(5);
  for (int x=0;x<173;x++) {
    currentSpeed=1023-x;
    Serial.println(currentSpeed);
    left();
    delay(125);
  }
  
  halt();
  Serial.println ("Right Test");
    countDown(5); 
  for (int x=0;x<173;x++) {
    currentSpeed=1023-x;
    Serial.println(currentSpeed);
    right();
    delay(125);
  }
  
  halt();
}

void readWhite(){
  Serial.println("Calibrate White");
  digitalWrite(13,HIGH);
  for(int x=0;x<15;x++){
  delay(500);
  printLDR();
  }
    for (int i = 0; i<5; i++){
      white[i] += analogRead(i);
    }
      digitalWrite(13,LOW);
delay(2500);    
}

void readBlack(){
  Serial.println("Calibrate Black");
  digitalWrite(13,HIGH);
  for(int x=0;x<15;x++){
  delay(500);
  printLDR();
  }
    for (int i = 0; i<5; i++){
      black[i] = analogRead(i);
    }
    digitalWrite(13,LOW);
    delay(2500);
}

void setThresholds(){
  for (int i = 0; i<5; i++){
    threshold[i] = (white[i]+black[i])/2;
  }
}

void updateLDRValues(){
  LDRValue=0;
  for (int i = 0; i<5; i++){
    if (analogRead(i)<threshold[i]){
      ldr[i]=0; //Black
      LDRValue++;
    }
    else {
      ldr[i]=1; //White
    }
  }
}

void printLDR () {
    for (int x=0;x<5;x++) {
    Serial.print(analogRead(x));
    Serial.print(" ");
  }
  Serial.println();
}

void halt(){
  analogWrite(motorAF, 0);
  analogWrite(motorAB, 0);
  analogWrite(motorBF, 0);
  analogWrite(motorBB, 0);
}

void forward(){
  if(ldr[1]+ldr[2]+ldr[3]==3) {
    analogWrite(motorAF, currentSpeed);
    analogWrite(motorBF, currentSpeed);    
  }
  else {
    if (ldr[1]) {
      analogWrite(motorAF, currentSpeed-80);//-80 to adjust turn
      analogWrite(motorBF, currentSpeed-10);//-10 is to compensate for difference in speed of motor    
    }
    else {
      analogWrite(motorAF, currentSpeed);
      analogWrite(motorBF, currentSpeed-10-80);//kept both for readability
    }
  }
}

void backward() {
  analogWrite(motorAB, currentSpeed);
  analogWrite(motorBB, currentSpeed);
}

void right(){
  analogWrite(motorAF, currentSpeed);
  analogWrite(motorBB, currentSpeed);
}

void left(){
  analogWrite(motorAB, currentSpeed);
  analogWrite(motorBF, currentSpeed);
}

void loop () {
  updateLDRValues();
  if (LDRValue==0) {
    halt();
    delay(500);
    backward();
    while(LDRValue>=2){updateLDRValues();}
    delay(500);
    halt();
  }
  else {
   forward();
  }
}