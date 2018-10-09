#include "MyRobot.h"

void MyRobot::drive(int rval,int lval){
  leftMotor.write(180-rval);
  rightMotor.write(lval);
}

void MyRobot::moveUp(){
  		  armMotor.write(180);
		  armMotor2.write(0);
}

void MyRobot::armHalt(){
  		  armMotor.write(90);
		  armMotor2.write(90);
}

void MyRobot::moveDown(){
  		  armMotor.write(0);
		  armMotor2.write(180);
}

void MyRobot::harvest(){
  harvesterMotor.write(120);
  delay(50);
  harvesterMotor.write(90);
}
void MyRobot::spit(){
  harvesterMotor.write(60);
}
void MyRobot::harvestStop(){
  harvesterMotor.write(90);
}

void MyRobot::turnMotorsOff(){
  harvestStop();
  armHalt();
  drive(90,90);
}
