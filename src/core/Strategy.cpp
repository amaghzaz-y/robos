#include "Strategy.h"

#define BLUE 1
#define YELLOW 0

void Strategy::setup()
{
	Serial.println("STRATEGY :: SETUP");
	currentInstruction = 0;
	display.setup();
	movement.setup();
	actuators.setup();
	neopixel.setup();
	sensors.setup();
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
		neopixel.changeColor(1);
	}
	if (digitalRead(TEAM_PIN) == 1)
	{
		movement.setTeam(1);
		team = 1;
		display.Show("TEAM", "BLUE", "", "");
		neopixel.changeColor(2);
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
	neopixel.changeColor(3);
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
		neopixel.changeColor(0);
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
	Point2D home_alpha = Point2D(300, 1700);
	Point2D home_beta = Point2D(300, 300);
	Point2D home_theta = Point2D(2775, 1000);

	Point2D alpha = Point2D(1000, 1300);
	Point2D beta = Point2D(1000, 700);
	Point2D tetha = Point2D(1500, 1500);

	Point2D b0 = Point2D(225, 1820);
	Point2D b1 = Point2D(850, 1820);
	Point2D b2 = Point2D(850, 1750);

	Point2D delta0 = Point2D(1300, 1600);
	Point2D delta1 = Point2D(500, 500);
	Point2D delta2 = Point2D(600, 225);
	Point2D delta3 = Point2D(1000, 225);
	Point2D delta4 = Point2D(1300, 400);
	Point2D delta5 = Point2D(1300, 1600);

	actuators.elevateAll();
	actuators.releaseAll();

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
	// 7. go to b0
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(b0, lidar);
	// 8. go to b1
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(b1, lidar);
	// 9. go to delta5
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(delta5, lidar);
	// 10. push theta to home theta
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(home_theta, lidar);
}

void Strategy::strat_YELLOW(bool *lidar)
{
	Point2D home_alpha = Point2D(3000 - 300, 1700);
	Point2D home_beta = Point2D(3000 - 300, 300);
	Point2D home_theta = Point2D(2775, 1000);

	Point2D alpha = Point2D(3000 - 1000, 1300);
	Point2D beta = Point2D(3000 - 1000, 700);
	Point2D tetha = Point2D(3000 - 1500, 1500);

	Point2D b0 = Point2D(3000 - 225, 1820);
	Point2D b1 = Point2D(3000 - 850, 1820);
	Point2D b2 = Point2D(3000 - 850, 1750);

	Point2D delta0 = Point2D(3000 - 1300, 1600);
	Point2D delta1 = Point2D(3000 - 500, 500);
	Point2D delta2 = Point2D(3000 - 600, 225);
	Point2D delta3 = Point2D(3000 - 1000, 225);
	Point2D delta4 = Point2D(3000 - 1300, 400);
	Point2D delta5 = Point2D(3000 - 1300, 1600);

	actuators.elevateAll();
	actuators.releaseAll();

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
	// 7. go to b0
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(b0, lidar);
	// 8. go to b1
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(b1, lidar);
	// 9. go to delta5
	movement.setSide(SIDE_C);
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

Point2D Strategy::getCurrentPoint()
{
	return movement.getCurrentPoint();
}
