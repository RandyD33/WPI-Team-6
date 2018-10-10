#include "MyRobot.h"

void MyRobot::drive(int rval,int lval){ // drive robot forward, runs until motors are stopped
  leftMotor.write(180-rval);
  rightMotor.write(lval);
}

void MyRobot::moveDown(){ // move arm down, runs until told to halt
  armMotor.write(180);
  armMotor2.write(0);
}

void MyRobot::armHalt(){ // tells arm to halt
  armMotor.write(90);
  armMotor2.write(90);
}

void MyRobot::moveUp(){ // move arm down, runs until told to halt
  armMotor.write(0);
  armMotor2.write(180);
}

void MyRobot::spit(){ // release orbs held in harvester, runs in discrete jumps to be gentle
  harvesterMotor.write(120);
  delay(50);
  harvesterMotor.write(90);
}

void MyRobot::harvest(){ // run harvester to collect orbs, runs until told to stop
  harvesterMotor.write(60);
}

void MyRobot::harvestStop(){ // tells harvester to stop
  harvesterMotor.write(90);
}

void MyRobot::turnMotorsOff(){ // shut off all motors
  harvestStop();
  armHalt();
  drive(90,90);
}
