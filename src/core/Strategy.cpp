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
		// movement.calibrate();
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
		Serial.println("team YELLOW");
	}
	if (digitalRead(TEAM_PIN) == 1)
	{
		movement.setTeam(1);
		team = 1;
		display.Show("TEAM", "BLUE", "", "");
		Serial.println("team BLUE");
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
	Serial.println(team);
}

void Strategy::start(bool *lidar)
{
	if (team == BLUE)
	{
		strat_BLUE(lidar);
	}
	if (team == YELLOW)
	{
		strat_YELLOW_V2(lidar);
	}
}

void Strategy::setPoints(Point2D *p, int len)
{
	points = p;
	arrayLength = len;
}

void Strategy::Initiation()
{
	while (!movement.isCalibrated())
	{
		init();
		teamSelection();
	}
}

// void Strategy::afterCalibration(bool *lidar)
// {
// 	if (team == 0)
// 	{
// 		Point2D center = Point2D(1225, 1775);
// 		movement.Execute(center, lidar);
// 	}
// 	if (team == 1)
// 	{
// 		Point2D center = Point2D(225, 1775);
// 		movement.Execute(center, lidar);
// 	}
// }

void Strategy::strat_YELLOW(bool *lidar)
{
	Point2D center = Point2D(2000, 1225);
	movement.setSide(SIDE_A);
	movement.Execute(center, lidar);
	Point2D p1 = Point2D(1700, 1225);
	movement.setSide(SIDE_A);
	movement.Execute(p1, lidar);
	Point2D p2 = Point2D(150, 300);
	movement.setSide(SIDE_A);
	movement.Execute(p1, lidar);
	stop();
}

void Strategy::strat_YELLOW_V2(bool *lidar)
{
	// put bannerzZs
	movement.Execute(Point2D(0, 1225), lidar);
	// go out
	movement.Execute(Point2D(300, 1225), lidar);
	// prepare
	movement.Execute(Point2D(500, 1000), lidar);
	movement.Execute(Point2D(500, 775), lidar);
	movement.Execute(Point2D(600, 775), lidar);
	// push cans
	movement.setSide(SIDE_A);
	movement.ExecuteSEMI(Point2D(100, 775), lidar);
	// go back
	movement.setSide(SIDE_BC);
	movement.ExecuteSEMI(Point2D(300, 775), lidar);
	// go home
	movement.ExecuteSEMI(Point2D(1775, 375), lidar);
	stop();
}

void Strategy::strat_BLUE(bool *lidar)
{
	Point2D center = Point2D(2000, 3000 - 1225);
	movement.setSide(SIDE_A);
	movement.Execute(center, lidar);
	Point2D p1 = Point2D(1700, 3000 - 1225);
	movement.setSide(SIDE_A);
	movement.Execute(p1, lidar);
	Point2D p2 = Point2D(150, 3000 - 300);
	movement.setSide(SIDE_A);
	movement.Execute(p1, lidar);
	stop();
}

void Strategy::Homologuation(bool *lidar)
{
	Point2D center = Point2D(2000, 3000 - 1225);
	movement.setSide(SIDE_A);
	movement.Execute(center, lidar);
	Point2D p1 = Point2D(1700, 3000 - 1225);
	movement.setSide(SIDE_A);
	movement.Execute(p1, lidar);
	Point2D p2 = Point2D(150, 3000 - 300);
	movement.setSide(SIDE_A);
	movement.Execute(p2, lidar);
	stop();
}

Point2D Strategy::getCurrentPoint()
{
	return movement.getCurrentPoint();
}
