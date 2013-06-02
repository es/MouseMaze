#include "Arduino.h"
#include "Mouse.h"

Mouse::Mouse(int motorLF, int motorLB, int motorRF, int motorRB){
    setSpeed(-1);
    setAdjust(-1);
    _motorLF=motorLF;
    _motorLB=motorLB;
    _motorRF=motorRF;
    _motorRB=motorRB;
}

void Mouse::compWheelDiff (int leftWheel, int rightWheel){
    _compLeftWheel=leftWheel;
    _compRightWheel=rightWheel;
}

void Mouse::setSpeed(int speed){
    if (speed==-1)
        _speed=1023;
    else
        _speed=speed;
}

void Mouse::setAdjust(int adjust) {
    if (adjust==-1)
        _adjust=50;
    else
        _adjust=adjust;
}

void Mouse::halt(){
    analogWrite(_motorLF, 0);
    analogWrite(_motorLB, 0);
    analogWrite(_motorRF, 0);
    analogWrite(_motorRB, 0);
}

void Mouse::forward(int option){
    //option==>0 forward, 1 adjust left, 2 adjust right
    if (_currentAction!=1){
        halt();
        _currentAction=1;
    }
    if(option==1){//go forward
        analogWrite(_motorLF, _speed-_compLeftWheel);
        analogWrite(_motorRF, _speed-_compRightWheel);        
    }
    else{
        if (option==2){//adjust left
            analogWrite(_motorLF, _speed-_compLeftWheel-_adjust);//-80 to adjust turn
            analogWrite(_motorRF, _speed-_compRightWheel);//-10 is to compensate for difference in speed of _motor        
        }
        else{
            if (option==3){//adjust right
                analogWrite(_motorLF, _speed-_compLeftWheel);
                analogWrite(_motorRF, _speed-_compRightWheel-_adjust);//kept both for readability
            }
        }
    }
}

void Mouse::reverse(){
    if (_currentAction!=2){
        halt();
        _currentAction=2;
    }
    analogWrite(_motorLB, _speed-_compLeftWheel);
    analogWrite(_motorRB, _speed-_compRightWheel);
}

void Mouse::left(){
    if (_currentAction!=3){
        halt();
        _currentAction=3;
    }
    //analogWrite(_motorLB, _speed-_compLeftWheel);
    analogWrite(_motorRF, _speed-_compRightWheel);
}

void Mouse::right(){
    if (_currentAction!=4){
        halt();
        _currentAction=4;
    }
    analogWrite(_motorLF, _speed-_compLeftWheel);
    //analogWrite(_motorRB, _speed-_compRightWheel);
}