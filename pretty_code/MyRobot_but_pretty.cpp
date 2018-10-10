#include "MyRobot.h"
#include "Arduino.h"

const int teleLED = 26;
const int autoLED = 25;

enum AutoStates { // enum variable to use in switch statement in autonomous
  DRIVE,
  LIFT,
  DUMP
}autoState;

void MyRobot::initialize(int rightMotorPin, int leftMotorPin, int armMotorPin,int armMotorPin2, int potPin, int harvesterPin, int rPhotoPin, int lPhotoPin){ // initialize all pins and motors
  armPotPin = potPin;
  pinMode(armPotPin, INPUT);

  leftPhotoPin = lPhotoPin;
  pinMode(leftPhotoPin, INPUT);

  rightPhotoPin = rPhotoPin;
  pinMode(rightPhotoPin, INPUT);

  rightMotor.attach(rightMotorPin, 1000, 2000);
  leftMotor.attach(leftMotorPin, 1000, 2000);
  harvesterMotor.attach(harvesterPin, 1000, 2000);
  armMotor.attach(armMotorPin, 1000, 2000);
  armMotor2.attach(armMotorPin2,1000,2000);
  
  autoState = LIFT; // begin autonomous in LIFT state
  running = false; // initialize 

  pinMode(teleLED,OUTPUT);
  pinMode(autoLED,OUTPUT);
}

int MyRobot::getDebugLEDPin(){ // leftover from debugging process
  return 13;
}

void MyRobot::robotStartup(){} // this is used by dfw, we don't need it but changing it creates unexpected behavior 

void MyRobot::autonomous( long time){
  Serial.print("\r\nAuto time remaining: ");
  Serial.print(time);
  
  digitalWrite(autoLED,HIGH); // light up LED telling us that the robot is in autonomous
  
  int lmotor;
  int rmotor;
  int aMotor;
		
  switch(autoState){
    case DRIVE: // second state robot should be in, checks jumper wire and calls appropriate driving function
      if(digitalRead(8)==HIGH){ // if jumper wire is connected
        lightBasedRed(); // call red side drive function
      }
	  else{
        lightBasedBlue(); // call blue side drive function
      }
      
	  autoState = DUMP; // once in position, dump balls
      break;
      
    case LIFT: // first state robot should be in, lifts arm to desired height
      Serial.println(analogRead(0));
      if(analogRead(armPotPin) < orbit3Val){ // if arm hasn't reached disired height, keep going
        moveUp();
      }
      if(analogRead(armPotPin) > orbit3Val){ // if arm reached height, stop
        armHalt();
        autoState=DRIVE; // once arm is lifted, drive to orbit
      }
      break;
        
    case DUMP: // last state in autonomous, gently dump orbs
      harvesterMotor.write(120);
      break;
  } // end switch
} // end 

void MyRobot::teleop( long time){
  digitalWrite(teleLED,HIGH); // turn on LED to tell us we're in autonomous
  if(time<20000){ 
    digitalWrite(autoLED,HIGH); // turn on LED if we're running out of time
  }
  else{
    digitalWrite(autoLED,LOW);
  }

  // Joystick controls
  //Run functions in the robot class
  if(dfw->joystickrv() > 92 || dfw->joystickrv() < 87){
    drive(dfw->joystickrv(),90);
  }
  if(dfw->joysticklv() > 92 || dfw->joysticklv() < 87){
    drive(90,dfw->joysticklv());
  }
  if((dfw->joystickrv() > 92 || dfw->joystickrv() < 87) && (dfw->joysticklv() > 92 || dfw->joysticklv() < 87)){
    drive(dfw->joystickrv(),dfw->joysticklv());
  }
  if(dfw->r2()){
    moveDown();
  }
  else if(dfw->r1()){
    moveUp();
  }
  else if(!dfw -> r1()&&!dfw -> r2()){
    armHalt();
  }
  if(dfw->l1()){
    spit();
  }
  if(dfw->l2() && !running){
    harvest();
    running = true;
  }
  else if(dfw -> l2() && running){
    harvestStop();
    running = false;
  }
}

void MyRobot::robotShutdown(void){ // turn off all the motors and celebrate our inevitable victory
  turnMotorsOff();
  digitalWrite(autoLED,LOW);
  digitalWrite(teleLED,LOW);
}
