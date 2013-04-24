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
A0 - LDR or Ultrasonic
A1 - LDR or Ultrasonic
A2 - LDR
A3 - LDR
A4 - LDR
A5 - Empty
*/

int redLED = 2; //LED pin indicating: Press button to set white values
int yellowLED = 3; //LED pin indicating: Press button to set black values
int greenLED = 4; //LED pin indicating: Press button to go
int button = 5; //Digital input for calibration button
int white [5]; //Value saved on white button press
int black [5]; //Value saved on black button press
int threshold [5]; //Average between white and black.
boolean ldr [5]; //1 if over black, 0 otherwise
int motorAF = 6; //Motor A forward pin
int motorAB = 7; //Motor A backward pin
int motorBF = 8; //Motor B forward pin
int morotBB = 9; //Motor B backward pin


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

void setLDRValues(){
  for (int i = 0; i<5; i++){
    if (analogRead(i)<threshold[i])
      ldr[i]=0;
    else
      ldr[i]=1;
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
