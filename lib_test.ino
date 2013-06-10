#include <Mouse.h>
Mouse mouse (6,9,10,11);
int LDRValue=0;
int option;

void setup () {
  mouse.setSpeed(890);//900,(0,20), 860 (0,10,10)
  mouse.compWheelDiff(10,25);
  mouse.setAdjust(13);
  Serial.begin(9600);
  Serial.println("NEW CODE!");
  Serial.println("Turn on white light");
  pinMode(13,OUTPUT);
  //digitalWrite(13,HIGH);
}

void countDown(int a) {
  for (int x=a;x>0;x--) {
    Serial.println(x);
    delay(1000);
  }
}

void printLDR () {
  for (int x=0;x<5;x++) {
    //Serial.print(analogRead(x));
    //Serial.print(" ");
  }
  //Serial.println();
}

void testWheels() {
  //digitalWrite(13,HIGH);
  countDown(5);
  //digitalWrite(13,LOW);
  mouse.forward(1);
  delay(500);
  mouse.halt();
  delay(500);
  mouse.swingRight();
  delay(1500);
  mouse.halt();
  delay(500);
  /*Serial.println ("Stop Test");
  countDown(5);
  mouse.forward(1);
  countDown(5);
  Serial.println("HALT!");
  mouse.halt();
  delay(3000);
  mouse.halt();

  Serial.println ("Forward (Straight) Test");
  countDown(5);
  mouse.forward(1);
  countDown(5);
  mouse.halt();
    
  Serial.println ("Forward (Adjust Left) Test");
  countDown(5);
  mouse.compWheelDiff(10,13);
  mouse.forward(2);
  mouse.compWheelDiff(0,13);
  countDown(5);
  mouse.halt();

  Serial.println ("Forward (Adjust Right) Test");
  countDown(5);
  mouse.compWheelDiff(0,20);
  mouse.forward(3);
  mouse.compWheelDiff(0,13);
  countDown(5);
  mouse.halt();

  Serial.println ("Backward Test");
  countDown(5); 
  mouse.reverse();
  countDown(5);
  mouse.halt();
  
  Serial.println ("Left Test");
  countDown(5);
  mouse.left();
  countDown(5);
  mouse.halt();
  
  Serial.println ("Right Test");
  countDown(5); 
  mouse.right();
  countDown(5);
  mouse.halt();

  Serial.println ("Swing Left Test");
  countDown(5);
  mouse.swingLeft();
  countDown(5);
  mouse.halt();
  
  Serial.println ("Swing Right Test");
  countDown(5); 
  mouse.swingRight();
  countDown(5);
  mouse.halt();*/
}

void loop () {
  testWheels();
}