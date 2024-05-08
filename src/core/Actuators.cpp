#include <core/Actuators.h>

void Actuators::pickObject(int SIDE)
{
	if (SIDE == SIDE_A_ID)
	{
		servoDriver.writeMicroseconds(SERVO_SIDE_A_L, FOLD_L);
		servoDriver.writeMicroseconds(SERVO_SIDE_A_R, FOLD_R);
		side_A_full = true;
	}
	if (SIDE == SIDE_B_ID)
	{
		servoDriver.writeMicroseconds(SERVO_SIDE_B_L, FOLD_L);
		servoDriver.writeMicroseconds(SERVO_SIDE_B_R, FOLD_R);
		side_B_full = true;
	}
	if (SIDE == SIDE_C_ID)
	{

		servoDriver.writeMicroseconds(SERVO_SIDE_C_L, FOLD_L);
		servoDriver.writeMicroseconds(SERVO_SIDE_C_R, FOLD_R);
		side_C_full = true;
	}
}

void Actuators::releaseObject(int SIDE)
{
	if (SIDE == SIDE_A_ID)
	{
		servoDriver.writeMicroseconds(SERVO_SIDE_A_L, RELEASE_L);
		servoDriver.writeMicroseconds(SERVO_SIDE_A_R, RELEASE_R);

		side_A_full = false;
	}
	if (SIDE == SIDE_B_ID)
	{
		servoDriver.writeMicroseconds(SERVO_SIDE_B_L, RELEASE_L);
		servoDriver.writeMicroseconds(SERVO_SIDE_B_R, RELEASE_R);
		side_B_full = false;
	}
	if (SIDE == SIDE_C_ID)
	{
		servoDriver.writeMicroseconds(SERVO_SIDE_C_L, RELEASE_L);
		servoDriver.writeMicroseconds(SERVO_SIDE_C_R, RELEASE_R);
		side_C_full = false;
	}
}

bool Actuators::isObjectPicked(int SIDE)
{
	if (SIDE == SIDE_A_ID)
	{
		return side_A_full;
	}
	if (SIDE == SIDE_B_ID)
	{
		return side_B_full;
	}
	if (SIDE == SIDE_C_ID)
	{
		return side_C_full;
	}
	else
	{
		return true;
	}
}

void Actuators::dropCherry()
{
	servoDriver.writeMicroseconds(SERVO_CHERRY_A, 2300);
	delay(20);
	servoDriver.writeMicroseconds(SERVO_CHERRY_B, 2300);
	delay(20);
	servoDriver.writeMicroseconds(SERVO_CHERRY_C, 2300);
	delay(20);
}
void Actuators::setup()
{
	Serial.println();
	Serial.println("Actuators :: setting up...");
	servoDriver.begin();
	servoDriver.setOscillatorFrequency(28000000);
	servoDriver.setPWMFreq(SERVO_FREQ);
	delay(500);
	releaseAll();
	delay(500);
	foldAll();
	delay(500);
	delevateAll();
	delay(500);
	Serial.println("Actuators :: setup done");
}

void Actuators::foldAll()
{
	servoDriver.writeMicroseconds(SERVO_SIDE_A_L, FOLD_L);
	servoDriver.writeMicroseconds(SERVO_SIDE_A_R, FOLD_R);
	servoDriver.writeMicroseconds(SERVO_SIDE_B_L, FOLD_L);
	servoDriver.writeMicroseconds(SERVO_SIDE_B_R, FOLD_R);
	servoDriver.writeMicroseconds(SERVO_SIDE_C_L, FOLD_L);
	servoDriver.writeMicroseconds(SERVO_SIDE_C_R, FOLD_R);
}

void Actuators::releaseAll()
{
	Serial.println("defolding");
	servoDriver.writeMicroseconds(SERVO_SIDE_A_L, RELEASE_L);
	servoDriver.writeMicroseconds(SERVO_SIDE_A_R, RELEASE_R);
	servoDriver.writeMicroseconds(SERVO_SIDE_B_L, RELEASE_L);
	servoDriver.writeMicroseconds(SERVO_SIDE_B_R, RELEASE_R);
	servoDriver.writeMicroseconds(SERVO_SIDE_C_L, RELEASE_L);
	servoDriver.writeMicroseconds(SERVO_SIDE_C_R, RELEASE_R);
	Serial.println("defolded");
}

void Actuators::performTEST()
{
	while (1)
	{
		delevateObject(SIDE_A_ID, 0);
		pickObject(SIDE_A_ID);
		delay(2000);
		elevateObject(SIDE_A_ID, 0);
		delay(2000);
		elevateObject(SIDE_A_ID, 1);
		delay(2000);
		elevateObject(SIDE_A_ID, 2);
		delay(2000);
		delevateObject(SIDE_A_ID, 2);
		delay(2000);
		delevateObject(SIDE_A_ID, 1);
		delay(2000);
		delevateObject(SIDE_A_ID, 0);
		delay(2000);
		releaseObject(SIDE_A_ID);
		delay(5000);
		delevateObject(SIDE_B_ID, 0);
		pickObject(SIDE_B_ID);
		delay(2000);
		elevateObject(SIDE_B_ID, 0);
		delay(2000);
		elevateObject(SIDE_B_ID, 1);
		delay(2000);
		elevateObject(SIDE_B_ID, 2);
		delay(2000);
		delevateObject(SIDE_B_ID, 2);
		delay(2000);
		delevateObject(SIDE_B_ID, 1);
		delay(2000);
		delevateObject(SIDE_B_ID, 0);
		delay(2000);
		releaseObject(SIDE_B_ID);
		delay(5000);
		delevateObject(SIDE_C_ID, 0);
		pickObject(SIDE_C_ID);
		delay(2000);
		elevateObject(SIDE_C_ID, 0);
		delay(2000);
		elevateObject(SIDE_C_ID, 1);
		delay(2000);
		elevateObject(SIDE_C_ID, 2);
		delay(2000);
		delevateObject(SIDE_C_ID, 2);
		delay(2000);
		delevateObject(SIDE_C_ID, 1);
		delay(2000);
		delevateObject(SIDE_C_ID, 0);
		delay(2000);
		releaseObject(SIDE_C_ID);
	}
}

void Actuators::elevateObject(int SIDE, int LEVEL)
{
	if (LEVEL == 1)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = (US_LEVEL_0); microsec < (US_LEVEL_1 + 150); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = US_LEVEL_0; microsec < (US_LEVEL_1 + 150); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = US_LEVEL_0; microsec < (US_LEVEL_1 + 150); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
	else if (LEVEL == 2)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = (US_LEVEL_1 + 150); microsec < (US_LEVEL_2 + 250); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = (US_LEVEL_1 + 150); microsec < (US_LEVEL_2 + 250); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = (US_LEVEL_1 + 150); microsec < (US_LEVEL_2 + 250); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
	else if (LEVEL == 3)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = (US_LEVEL_2 + 250); microsec < (US_LEVEL_3 + 300); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = (US_LEVEL_2 + 250); microsec < (US_LEVEL_3 + 300); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = (US_LEVEL_2 + 250); microsec < (US_LEVEL_3 + 300); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
}

void Actuators::funnyAction()
{
	servoDriver.setPin(SERVO_FUNNY_ACTION, 4095);
	delay(15000);
	servoDriver.setPin(SERVO_FUNNY_ACTION, 0);
}

void Actuators::dropCherryStream()
{
	servoDriver.writeMicroseconds(SERVO_CHERRY_DROP, 1900);
}

void Actuators::delevateObject(int SIDE, int LEVEL)
{
	if (LEVEL == 0)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = US_LEVEL_1; microsec > 480; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = US_LEVEL_1; microsec > US_LEVEL_0; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = US_LEVEL_1; microsec > US_LEVEL_0; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
	else if (LEVEL == 1)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = US_LEVEL_2; microsec > US_LEVEL_1; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = US_LEVEL_2; microsec > US_LEVEL_1; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = US_LEVEL_2; microsec > US_LEVEL_1; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
	else if (LEVEL == 2)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = US_LEVEL_3; microsec > US_LEVEL_2; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = US_LEVEL_3; microsec > US_LEVEL_2; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = US_LEVEL_3; microsec > US_LEVEL_2; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
}

void Actuators::delevateAll()
{
	delevateObject(SIDE_A_ID, 0);
	delevateObject(SIDE_B_ID, 0);
	delevateObject(SIDE_C_ID, 0);
}

void Actuators::initCook()
{
	releaseObject(SIDE_A_ID);
	releaseObject(SIDE_B_ID);
	releaseObject(SIDE_C_ID);
	delay(5000);
	pickObject(SIDE_A_ID);
	pickObject(SIDE_B_ID);
	pickObject(SIDE_C_ID);
	elevateObject(SIDE_A_ID, 1);
	elevateObject(SIDE_B_ID, 1);
	elevateObject(SIDE_C_ID, 1);
}

void Actuators::normalize()
{
	delevateObject(SIDE_A_ID, 0);
	delevateObject(SIDE_B_ID, 0);
	delevateObject(SIDE_C_ID, 0);
	releaseObject(SIDE_A_ID);
	releaseObject(SIDE_B_ID);
	releaseObject(SIDE_C_ID);
	elevateObject(SIDE_A_ID, 2);
	elevateObject(SIDE_B_ID, 2);
	elevateObject(SIDE_C_ID, 2);
}