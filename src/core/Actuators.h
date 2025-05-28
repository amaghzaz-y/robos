#pragma once
#include <Arduino.h>
#include "lib/pwnservo/Adafruit_PWMServoDriver.h"

#define SERVOMIN 150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 1500	 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 1750	 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600

#define FOLD_R 500
#define RELEASE_R 1700

#define FOLD_L 1900
#define RELEASE_L 1000

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

#define US_LEVEL_0 450
#define US_LEVEL_1 750
#define US_LEVEL_2 900
#define US_LEVEL_3 1150

#define PUMP_PLANK 15
#define PUMP_PLANK_VALVE 14

#define PUMP_LEFT_CAN 13
#define PUMP_LEFT_CAN_VALVE 12

#define PUMP_RIGHT_CAN 11
#define PUMP_RIGHT_CAN_VALVE 10

#define LEFT_ARM 2
#define LEFT_ELEVATOR 1

#define RIGHT_ARM 0
#define RIGHT_ELEVATOR 3

class Actuators
{
private:
	Adafruit_PWMServoDriver driver;

public:
	void setup();

	void pumpUp(bool hold = false);
	void pumpLeft(bool hold = false);
	void pumpRight(bool hold = false);
	void slide(bool up = false);
	void leftArm(bool hold = false);
	void rightArm(bool hold = false);
};
