#include <core/Actuators.h>

void Actuators::setup()
{
	Serial.println();
	Serial.println("Actuators :: starting setup up");
	driver.begin();
	driver.setOscillatorFrequency(28000000);
	driver.setPWMFreq(50);
	delay(100);
	// set initial setup
	pumpUp(false);
	pumpLeft(false);
	pumpRight(false);
	slide(true);
	leftArm(false);
	rightArm(false);
	Serial.println("Actuators :: setup done");
}

void Actuators::pumpUp(bool hold)
{
	Serial.print("PUMP_UP : ");
	Serial.println(hold);
	if (hold)
	{
		driver.setPWM(PUMP_PLANK, 0, 4096);
		driver.setPWM(PUMP_PLANK_VALVE, 4096, 0);
	}
	else
	{
		driver.setPWM(PUMP_PLANK, 4096, 0);
		driver.setPWM(PUMP_PLANK_VALVE, 0, 4096);
	}
}

void Actuators::pumpLeft(bool hold)
{
	Serial.print("PUMP_LEFT : ");
	Serial.println(hold);
	if (hold)
	{
		driver.setPWM(PUMP_LEFT_CAN, 0, 4096);
		driver.setPWM(PUMP_LEFT_CAN_VALVE, 4096, 0);
	}
	else
	{
		driver.setPWM(PUMP_LEFT_CAN, 4096, 0);
		driver.setPWM(PUMP_LEFT_CAN_VALVE, 0, 4096);
	}
}

void Actuators::pumpRight(bool hold)
{
	Serial.print("PUMP_RIGHT : ");
	Serial.println(hold);
	if (hold)
	{
		driver.setPWM(PUMP_RIGHT_CAN, 4096, 0);
		driver.setPWM(PUMP_RIGHT_CAN_VALVE, 0, 4096);
	}
	else
	{
		driver.setPWM(PUMP_RIGHT_CAN, 0, 4096);
		driver.setPWM(PUMP_RIGHT_CAN_VALVE, 4096, 0);
	}
}

void Actuators::slide(bool up)
{
	Serial.print("SLIDE : ");
	Serial.println(up);
	if (up)
	{
		driver.writeMicroseconds(LEFT_ELEVATOR, 2300);
		driver.writeMicroseconds(RIGHT_ELEVATOR, 900);
	}
	else
	{
		driver.writeMicroseconds(LEFT_ELEVATOR, 1525);
		driver.writeMicroseconds(RIGHT_ELEVATOR, 1800);
	}
}

void Actuators::leftArm(bool hold)
{
	Serial.print("LEFT_ARM : ");
	Serial.println(hold);
	if (hold)
	{
		driver.writeMicroseconds(LEFT_ARM, FOLD_L);
	}
	else
	{
		driver.writeMicroseconds(LEFT_ARM, RELEASE_L);
	}
}

void Actuators::rightArm(bool hold)
{
	Serial.print("RIGHT_ARM : ");
	Serial.println(hold);
	if (hold)
	{
		driver.writeMicroseconds(RIGHT_ARM, FOLD_R);
	}
	else
	{
		driver.writeMicroseconds(RIGHT_ARM, RELEASE_R);
	}
}
