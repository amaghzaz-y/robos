#include "Strategy.h"

#define BLUE 1
#define YELLOW 0

void Strategy::setup()
{
	Serial.println("STRATEGY :: SETUP");
	currentInstruction = 0;
	display.setup();
	// movement.setup();
	// actuators.setup();
	// neopixel.setup();
	// sensors.setup();
	pinMode(INIT_PIN, INPUT_PULLUP);
	pinMode(REED_PIN, INPUT_PULLUP);
	pinMode(TEAM_PIN, INPUT_PULLUP);
	Serial.println("STRATEGY :: SETUP DONE");
}

void Strategy::init()
{
	if (digitalRead(INIT_PIN) == 0)
	{
		Serial.println("Starting Calibration");
		display.Show("STARTING", "CALIBRATION", "", "");
		actuators.releaseAll();
		movement.Calibrate();
	}
	else
	{
		Serial.println("Waiting for init...");
	}
}

void Strategy::teamSelection()
{
	if (digitalRead(TEAM_PIN) == 0)
	{
		movement.setTeam(0);
		team = 0;
		display.Show("TEAM", "YELLOW", "", "");
		// neopixel.changeColor(1);
	}
	if (digitalRead(TEAM_PIN) == 1)
	{
		movement.setTeam(1);
		team = 1;
		display.Show("TEAM", "BLUE", "", "");
		// neopixel.changeColor(2);
	}
}

void Strategy::testINPUT()
{
	Serial.print("REED : ");
	Serial.print(digitalRead(REED_PIN));
	Serial.print("   INIT : ");
	Serial.print(digitalRead(INIT_PIN));
	Serial.print("   TEAM : ");
	Serial.print(digitalRead(TEAM_PIN));
	Serial.println();
	// Serial.print("   L4 : ");
	// Serial.println(digitalRead(PIN_L4));
}

void Strategy::stop()
{
	Serial.println("FULL STOP IS INITIATED");
	// display.Show("FULL", "STOP", "FULL", "STOP");
	movement.FullStop();
	// neopixel.changeColor(3);
	Serial.println("FULL STOP HAS BEEN COMPLETE");
	// display.Show("SCORE:", "45", "SCORE:", "45");
}

void Strategy::Ready()
{
	while (digitalRead(REED_PIN) == 1)
	{
		delay(10);
	};
	while (digitalRead(REED_PIN) == 0)
	{
		delay(10);
	};
	if (digitalRead(REED_PIN) == 1)
	{
		Serial.println("GOOOOOO");
		// neopixel.changeColor(0);
	}
	// Serial.println("ready");
}

void Strategy::start(bool *lidar)
{
	if (team == BLUE)
	{
		strat_BLUE(lidar);
	}
	if (team == YELLOW)
	{
		strat_YELLOW(lidar);
	}
}

void Strategy::setPoints(Point2D *p, int len)
{
	points = p;
	arrayLength = len;
}

void Strategy::Initiation()
{
	while (!movement.isCalibrated() || !movement.atHome())
	{
		init();
		teamSelection();
	}
}

void Strategy::dropAllCherries()
{
	actuators.dropCherryStream();
	delay(2000);
	movement.rotateTo(SIDE_CA);
	movement.runSync();
}

void Strategy::afterCalibration(bool *lidar)
{
	if (team == 0)
	{
		Point2D center = Point2D(225, 225);
		movement.Execute(center, lidar);
	}
	if (team == 1)
	{
		Point2D center = Point2D(225, 1775);
		movement.Execute(center, lidar);
	}
}

void Strategy::strat_BLUE(bool *lidar)
{
	// homes
	Point2D home_alpha = Point2D(300, 1700);
	Point2D home_beta = Point2D(300, 300);
	Point2D home_theta = Point2D(2775, 1000);

	// flowers
	Point2D alpha = Point2D(1000, 1300);
	Point2D beta = Point2D(1000, 700);
	Point2D tetha = Point2D(1500, 1500);

	// flags checkpoints
	Point2D b0 = Point2D(225, 1820);
	Point2D b1 = Point2D(850, 1820);
	Point2D b2 = Point2D(850, 1750);

	// checkpoints
	Point2D delta0 = Point2D(1300, 1600);
	Point2D delta1 = Point2D(500, 500);
	Point2D delta2 = Point2D(600, 225);
	Point2D delta3 = Point2D(1000, 225);
	Point2D delta4 = Point2D(1300, 400);
	Point2D delta5 = Point2D(1250, 1650);

	actuators.elevateAll();
	actuators.releaseAll();

	// turn flags
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(b0, lidar);
	movement.setSide(SIDE_CA);
	movement.ExecuteSEMI(b1, lidar);
	movement.setSide(30);
	movement.ExecuteSEMI(b2, lidar);
	// 1. go to delta 0
	movement.setSide(SIDE_A);
	movement.ExecuteSEMI(delta0, lidar);
	// 2. push alpha to home beta
	actuators.delevateObject(SIDE_B_ID, 0);
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(home_beta, lidar);
	// 3. go to delta 1
	movement.setSide(SIDE_CA);
	movement.ExecuteSEMI(delta1, lidar);
	// 3. go to delta 2
	movement.setSide(SIDE_A);
	movement.ExecuteSEMI(delta2, lidar);
	// 4. go to delta 3
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(delta3, lidar);
	// 5. go to delta 4
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(delta4, lidar);
	// 6.  push beta to home alpha
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(home_alpha, lidar);
	// 7. go to delta5
	movement.setSide(SIDE_AB);
	movement.ExecuteSEMI(delta5, lidar);
	// 8. push theta to home theta
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(home_theta, lidar);
}

void Strategy::strat_YELLOW(bool *lidar)
{
	// homes
	Point2D home_alpha = Point2D(3000 - 300, 1700);
	Point2D home_beta = Point2D(3000 - 300, 300);
	Point2D home_theta = Point2D(3000 - 2775, 1000);

	// flowers
	Point2D alpha = Point2D(3000 - 1000, 1300);
	Point2D beta = Point2D(3000 - 1000, 700);
	Point2D tetha = Point2D(3000 - 1500, 1500);

	// flags checkpoints
	Point2D b0 = Point2D(3000 - 225, 1820);
	Point2D b1 = Point2D(3000 - 850, 1820);
	Point2D b2 = Point2D(3000 - 850, 1750);

	// checkpoints
	Point2D delta0 = Point2D(3000 - 1300, 1600);
	Point2D delta1 = Point2D(3000 - 500, 500);
	Point2D delta2 = Point2D(3000 - 600, 225);
	Point2D delta3 = Point2D(3000 - 1000, 225);
	Point2D delta4 = Point2D(3000 - 1300, 400);
	Point2D delta5 = Point2D(3000 - 1250, 1650);

	actuators.elevateAll();
	actuators.releaseAll();
	// turn flags
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(b0, lidar);
	movement.setSide(SIDE_BC);
	movement.ExecuteSEMI(b1, lidar);
	movement.setSide(30);
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(b2, lidar);

	// 1. go to delta 0
	movement.setSide(SIDE_A);
	movement.ExecuteSEMI(delta0, lidar);
	// 2. push alpha to home beta
	actuators.delevateObject(SIDE_B_ID, 0);
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(home_beta, lidar);
	// 3. go to delta 1
	movement.setSide(SIDE_CA);
	movement.ExecuteSEMI(delta1, lidar);
	// 3. go to delta 2
	movement.setSide(SIDE_A);
	movement.ExecuteSEMI(delta2, lidar);
	// 4. go to delta 3
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(delta3, lidar);
	// 5. go to delta 4
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(delta4, lidar);
	// 6.  push beta to home alpha
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(home_alpha, lidar);
	// 9. go to delta5
	movement.setSide(SIDE_CA);
	movement.ExecuteSEMI(delta5, lidar);
	// 10. push theta to home theta
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(home_theta, lidar);
}

void Strategy::Homologuation(bool *lidar)
{
	Point2D middle = Point2D(575, 1000);
	Point2D home2 = Point2D(225, 225);

	if (team == BLUE)
	{
		movement.setSide(SIDE_A);
		movement.ExecuteSEMI(middle, lidar);
		movement.ExecuteSEMI(home2, lidar);
	}
}

void Strategy::CoupOff()
{
	int time_elapsed = 0;
	actuators.elevateAll();
	time_elapsed = millis() - time_elapsed;
	// 10 start , 17 change, 23, 29, 38 laser, 42 pause, 46, dance, 64 stop
	while (1)
	{
		if (digitalRead(REED_PIN) == 1)
			break;
	}
	// neopixel.pride();
	delay(10000);
	while (time_elapsed < 17 * 1000)
	{
		time_elapsed = millis() - time_elapsed;
		// neopixel.changeColor(0);

		actuators.delevateAll();
		actuators.foldAll();
		movement.rotateTo(45.0);
		movement.runSync();
		// neopixel.pride();
		movement.rotateTo(-45.0);
		movement.runSync();
		actuators.elevateAll();
		actuators.releaseAll();
		delay(500);
	}

	// neopixel.changeColor(2);
	while (time_elapsed < 23 * 1000)
	{
		time_elapsed = millis() - time_elapsed;
		movement.rotateTo(20);
		movement.runSync();
	}

	// neopixel.changeColor(0);
	while (time_elapsed < 29 * 1000)
	{
		time_elapsed = millis() - time_elapsed;
		actuators.delevateAll();
		actuators.foldAll();
		// neopixel.changeColor(0);
		movement.rotateTo(20.0);
		movement.runSync();
		actuators.elevateAll();
		actuators.releaseAll();
		// neopixel.changeColor(3);
		delay(500);
	}
	// neopixel.pride();
	while (time_elapsed < 38 * 1000)
	{
		time_elapsed = millis() - time_elapsed;
		actuators.delevateObject(SIDE_A_ID, 1);
		actuators.delevateObject(SIDE_B_ID, 1);
		actuators.delevateObject(SIDE_C_ID, 1);
		delay(500);
		actuators.delevateObject(SIDE_A_ID, 1);
		actuators.delevateObject(SIDE_B_ID, 1);
		actuators.delevateObject(SIDE_C_ID, 1);
		delay(500);
		actuators.elevateObject(SIDE_A_ID, 2);
		actuators.elevateObject(SIDE_B_ID, 2);
		actuators.elevateObject(SIDE_C_ID, 2);
		delay(500);
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		actuators.elevateObject(SIDE_C_ID, 3);
		movement.setRotation(280);
		movement.runSync();
	}

	while (time_elapsed < 42 * 1000)
	{
		time_elapsed = millis() - time_elapsed;
		movement.rotateTo(270);
		movement.runSync();
		// neopixel.changeColor(0);
		time_elapsed = millis() - time_elapsed;
		movement.rotateTo(-270);
		movement.runSync();
		// neopixel.pride();
	}

	// neopixel.pride();
	while (time_elapsed < 46 * 1000)
	{
		time_elapsed = millis() - time_elapsed;
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		actuators.elevateObject(SIDE_C_ID, 3);
		// neopixel.changeColor(1);
		movement.rotateTo(30);
		movement.runSync();
		movement.rotateTo(30);
		movement.runSync();
		actuators.delevateObject(SIDE_A_ID, 1);
		actuators.delevateObject(SIDE_B_ID, 2);
		actuators.delevateObject(SIDE_C_ID, 1);
		// neopixel.pride();
		movement.rotateTo(270);
		movement.runSync();
	}
	while (time_elapsed < 64 * 1000)
	{
		time_elapsed = millis() - time_elapsed;
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		actuators.elevateObject(SIDE_C_ID, 3);
		movement.rotateTo(360);
		movement.runSync();
		// neopixel.changeColor(1);
		actuators.delevateObject(SIDE_A_ID, 1);
		actuators.delevateObject(SIDE_B_ID, 2);
		actuators.delevateObject(SIDE_C_ID, 1);
		movement.rotateTo(-360);
		movement.runSync();
		// neopixel.pride();
	}
}

Point2D Strategy::getCurrentPoint()
{
	return movement.getCurrentPoint();
}
