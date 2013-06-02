#ifndef Mouse_h
#define Mouse_h

#include "Arduino.h"

class Mouse
{
	public:
		Mouse(int motorLF, int motorLB, int motorRF, int motorRB);
		void compWheelDiff (int leftWheel, int rightWheel);
		void setSpeed(int speed);
		void setAdjust(int adjust);
		void forward(int option);//0 forward, 1 left, 2 right
		void reverse();
		void left();
		void right();
		void halt();
	private:
		int _speed;
		int _adjust;
		int _motorLF;
		int _motorLB;
		int _motorRF;
		int _motorRB;
		int _compLeftWheel;
		int _compRightWheel;
		int _currentAction;//1-forward,2-backward,3-left, 4-right
};
#endif