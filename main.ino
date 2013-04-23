/* Pin Map:
Digital:
0 - Avoid if possible. Serial output
1 - Avoid if possible. Serial output
2 - Red LED
3 - Yellow LED
4 - Green LED
5 - Calibration button
6 - Motor 1A
7 - Motor 1B
8 - Motor 2A
9 - Motor 2B
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

int redLED = 2; //LED pin indicating: Press button to set white values
int yellowLED = 3; //LED pin indicating: Press button to set black values
int greenLED = 4; //LED pin indicating: Press button to go
int button = 5; //Digital input for calibration button
int[5] white; //Value saved on white button press
int[5] black; //Value saved on black button press
int[5] threshold; //Average between white and black.
boolean[5] ldr; //1 if over black, 0 otherwise

void setup(){
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(button, INPUT);
  readWhite();
  readBlack();
  setThresholds();
}

void readWhite(){
  digitalWrite(redLED, HIGH);
  while(digitalRead(button) != HIGH){}
  for (int i = 0; i<5; i++){
    white[i] = analogRead(i);
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
