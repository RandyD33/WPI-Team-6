#include "MyRobot.h"
#include "Arduino.h"
/**
 * These are the execution runtions
 */


enum AutoStates {
  DRIVE,
  LIFT,
  DUMP
}autoState;

void MyRobot::initialize(int rightMotorPin, int leftMotorPin, int armMotorPin,int armMotorPin2, int potPin, int harvesterPin, int rPhotoPin, int lPhotoPin){
  
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
  autoState = LIFT;
  running = false;

  if(digitalRead(53)==HIGH){
    orbitVal = 580;
  }else{
    orbitVal = 290;
  }

  pinMode(25,OUTPUT);
  pinMode(26,OUTPUT);
}

int MyRobot::getDebugLEDPin(){
  return 13;
}

/**
 * Called when the start button is pressed and the robot control begins
 */
 void MyRobot::robotStartup(){

 } 
/**
 * Called by the controller between communication with the wireless controller
 * during autonomous mode
 * @param time the amount of time remaining
 * @param dfw instance of the DFW controller
 */
 void MyRobot::autonomous( long time){
		Serial.print("\r\nAuto time remaining: ");
		Serial.print(time);

		  digitalWrite(25,HIGH);

		int lmotor;
		int rmotor;
		int aMotor;
		
    switch(autoState){
      case DRIVE:
        if(digitalRead(52)==HIGH && digitalRead(53) == HIGH){
          lightBasedRed();
        }else if(digitalRead(52) == LOW && digitalRead(53)==HIGH){
          lightBasedBlue();
        }
         if(digitalRead(52)==HIGH && digitalRead(53) == LOW){
          timeBasedRed();
        }else if(digitalRead(52) == LOW && digitalRead(53)==LOW){
          timeBasedBlue();
        }
        
        autoState = DUMP;
        break;
      
      case LIFT:
      Serial.println(analogRead(0));
        if(analogRead(armPotPin) < orbitVal){
          moveUp();
        }
         if(analogRead(armPotPin) > orbitVal){
          armHalt();
          autoState=DRIVE;
        }
     
        break;
        
      case DUMP:
        harvesterMotor.write(120);
        break;
      
    }
    
 }
 
/**
 * Called by the controller between communication with the wireless controller
 * during teleop mode
 * @param time the amount of time remaining
 * @param dfw instance of the DFW controller
 */
 void MyRobot::teleop( long time){
   
		  digitalWrite(26,HIGH);
		if(time<20000){
      digitalWrite(25,HIGH);
		}else{
     digitalWrite(25,LOW);
    }
		//Run functions in the robot class
		if(dfw->joystickrv() > 92 || dfw->joystickrv() < 87){
		  drive(dfw->joystickrv(),90);
		}	if(dfw->joysticklv() > 92 || dfw->joysticklv() < 87){
		  drive(90,dfw->joysticklv());
		}	if((dfw->joystickrv() > 92 || dfw->joystickrv() < 87) && (dfw->joysticklv() > 92 || dfw->joysticklv() < 87)){
		  drive(dfw->joystickrv(),dfw->joysticklv());
		}
		
		if(dfw->r2()){
		  moveDown();
		}else if(dfw->r1()){
		  moveUp();
		}else if(!dfw -> r1()&&!dfw -> r2()){
     armHalt();     
    }
		
		if(dfw->l1()){
		  spit();
		
		}if(dfw->l2() && !running){
		  harvest();
		  running = true;
		}else if(dfw -> l2() && running){
		  harvestStop();
		  running = false;
		}
 }
/**
 * Called at the end of control to reset the objects for the next start
 */
 void MyRobot::robotShutdown(void){
		turnMotorsOff();
    digitalWrite(25,LOW);
    digitalWrite(26,LOW);

 }
