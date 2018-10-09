#pragma once

#include "Servo.h"
#include <DFW.h>
#include <AbstractDFWRobot.h>

class MyRobot :public AbstractDFWRobot{
public:
	DFW * dfw;
	/**
	 * Called when the start button is pressed and the robot control begins
	 */
	 void robotStartup();
	/**
	 * Called by the controller between communication with the wireless controller
	 * during autonomous mode
	 * @param time the amount of time remaining
	 * @param dfw instance of the DFW controller
	 */
	 void autonomous( long time);
	/**
	 * Called by the controller between communication with the wireless controller
	 * during teleop mode
	 * @param time the amount of time remaining
	 * @param dfw instance of the DFW controller
	 */
	 void teleop( long time);
	/**
	 * Called at the end of control to reset the objects for the next start
	 */
	 void robotShutdown(void);
	void initialize(int rightMotorPin, int leftMotorPin, int armMotorPin, int armMotorPin2, int ptotPin, int harvesterPin, int rPhotoPin, int lPhotoPin);
int getDebugLEDPin(void);
	~MyRobot(){};
private:
	int armPotPin;
	int bumbPin;
	int rightPhotoPin;
	int leftPhotoPin;
	Servo leftMotor;
	Servo rightMotor;
	Servo armMotor;
	Servo armMotor2;
	Servo harvesterMotor;
	void drive(int rval, int lval);
	void moveUp();
	void armHalt();
	void moveDown();
	void harvest();
	void spit();
	void harvestStop();
	const int DARK = 30;
	const int MID = 70;
	const int LIGHT = 200;
	const int orbit3Val = 580;
	const int k = 10;
	bool running;
 void turnMotorsOff();
 void timeBasedRed();
void timeBasedBlue();
 void lightBasedRed();
void lightBasedBlue();
};
