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

#include <Math.h>
int white [5]; //Value saved on white button press
int black [5]; //Value saved on black button press
int green [5]; //Value saved on green button press
int threshold [5]; //Average between white and black.
boolean ldr [5]; //1 if over black, 0 otherwise; ldr[0] is rightest, ldr[4] is leftest
boolean isFinished = false;

#include <Mouse.h>
Mouse mouse (6,9,10,11);
int LDRValue=0;
int option;

void setup () {
  mouse.setSpeed(890);//900,(0,20), 860 (0,10,10)
  mouse.compWheelDiff(0,35);
  //mouse.setAdjust(13);
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  readWhite();
  readBlack();
  //readGreen();
  setThresholds();
  Serial.println("SET IT ON THE TRACK MOTHERFUCKER");
  delay(2500);
}

void readWhite(){
  Serial.println("Calibrate White");
  digitalWrite(13,HIGH);
  for(int x=0;x<10;x++){
    delay(250);
    printLDR();
  }
  for (int i = 0; i<5; i++){
    white[i] += analogRead(i);
  }
  digitalWrite(13,LOW);
  delay(2500);    
}

void readGreen() {
  Serial.println("Calibrate Green");
  digitalWrite(13,HIGH);
  for(int x=0;x<10;x++) {
    delay(250);
    printLDR();
  }
  for (int i = 0; i<5; i++){
    green[i] = analogRead(i);
  }
  digitalWrite(13,LOW);
}

void readBlack() {
  Serial.println("Calibrate Black");
  digitalWrite(13,HIGH);
  for(int x=0;x<10;x++) {
    delay(250);
    printLDR();
  }
  for (int i = 0; i<5; i++){
    black[i] = analogRead(i);
  }
  digitalWrite(13,LOW);
  delay(2500);
}

void setThresholds() {
  for (int i = 0; i<5; i++){
    threshold[i] = (white[i]+black[i])/2;
  }
}

void updateLDRValues() {
  LDRValue=0;
  for (int i = 0; i<5; i++){
    if (analogRead(i)<threshold[i]){
      Serial.print (i);
      Serial.print ("black ");
      ldr[i]=1; //Black
      if (i==1||i==2||i==3)
        LDRValue++;
    }
    else {
      ldr[i]=0; //White
      Serial.print (i);
      Serial.print ("white ");
    }
  }
  Serial.println();
  /*if (LDRValue==0)
    Serial.println("LDRValue ZER0!");*/
}

void printLDR () {
  for (int x=0;x<5;x++) {
    Serial.print(analogRead(x));
    Serial.print(" ");
  }
  Serial.println();
}

boolean reallyOnWhite() {
  for (int i=0;i<5;i++) {
    updateLDRValues();
    if (LDRValue!=0)
      return false;
  }
  return true;
}

void dance () {
 mouse.left();
 mouse.halt();
 delay(2000);
 mouse.right();
}

boolean onGreen() {
  for (int i=0;i<5;i++) {
    if (!abs(green[i]-ldr[i])<5)
      return false;
  }
  return true;
}

void loop () {
  /*while(true){updateLDRValues();}*/
  updateLDRValues();
  if (onGreen()) {
    delay(1000);
    mouse.halt();
    while(true){dance();};
  }
  if (ldr[0]) {
    mouse.halt();
    //delay(750);
    //digitalWrite(13,HIGH);
    //Serial.println("Found right turn");
    mouse.right();
    delay(2100);
    mouse.halt();
    //Serial.println("Found right track");
    delay(500);
  }
  else if (LDRValue==0) {
    mouse.halt();
    if(reallyOnWhite()) {
        //digitalWrite(13,LOW);
        //mouse.reverse();
        //delay(750);
        mouse.halt();
        //delay(2000);
        //Serial.println("Found left turn");
        mouse.left();
        delay(2200);
        mouse.halt();
        //Serial.println("Found left track");
        delay(500);
    }
  }
  else {
    digitalWrite(13,LOW);
    //Serial.println("Going forward");
    if(LDRValue==3||ldr[2]) {
      option=1;//forward  
    }
    else {
      if (ldr[3]) {
        option=2;//adjsut left
        //mouse.compWheelDiff(10,13);
      }
      else {
        option=3;//adjsut right
        //mouse.compWheelDiff(0,20);
      }
    }
    mouse.forward(option);
    //delay(500);
    //mouse.compWheelDiff(0,13);
  }
}