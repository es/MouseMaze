int redLED = 2; //LED pin indicating: Press button to set white values
int yellowLED = 3; //LED pin indicating: Press button to set black values
int greenLED = 4; //LED pin indicating: Press button to go
int button = 5; //Digital input for button
int[5] white; //Value saved on white button press
int[5] black; //Value saved on black button press
int[5] threshold; //Average between white and black.

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
