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
	else
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
	while (currentInstruction < arrayLength)
	{
		movement.Execute(points[currentInstruction], lidar);
		currentInstruction++;
	}
	movement.goHome();
	currentInstruction = 0;
}

void Strategy::startDebug(bool *lidar)
{
	delay(2000);
	Serial.println("Starting...");
	while (currentInstruction < arrayLength)
	{
		movement.ExecuteSEMI(points[currentInstruction], lidar);
		currentInstruction++;
	}
	movement.goHomeSEMI();
	currentInstruction = 0;
}

void Strategy::startSEMI(bool *lidar)
{

	while (currentInstruction < arrayLength)
	{
		if (currentInstruction == 1)
		{
			movement.setSide(SIDE_B);
		}
		if (currentInstruction == 2)
		{
			movement.setSide(SIDE_C);
		}
		movement.ExecuteSEMI(points[currentInstruction], lidar);
		// actuators.pickObject(0);
		delay(2000);
		currentInstruction++;
	}
	movement.goHomeSEMI();
	currentInstruction = 0;
}

void Strategy::startSEMIOFFSET(bool *lidar)
{
	while (currentInstruction < arrayLength)
	{
		if (currentInstruction == 1)
		{
			movement.setSide(SIDE_B);
		}
		if (currentInstruction == 2)
		{
			movement.setSide(SIDE_C);
		}
		if (currentInstruction == 2)
		{
			actuators.releaseObject(0);
		}
		movement.ExecuteSEMIOFFSET(points[currentInstruction], lidar);
		if (currentInstruction == 2)
		{
			actuators.pickObject(0);
			actuators.elevateObject(SIDE_C_ID, 2);
		}
		else
		{
			delay(2000);
		}
		currentInstruction++;
	}
	movement.goHomeSEMI();
	actuators.delevateObject(SIDE_C_ID, 1);
	actuators.delevateObject(SIDE_C_ID, 0);
	actuators.releaseObject(0);
	currentInstruction = 0;
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

void Strategy::stratA(bool *lidar)
{
	Point2D batch_alpha = Point2D(1000, 1300);
	Point2D batch_beta = Point2D(1000, 700);
	if (team == BLUE)
	{
		// 1. pick first batch from alpha
		movement.setSide(SIDE_A);
		actuators.foldAll();
		actuators.delevateAll();
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMI(batch_alpha, lidar);
		actuators.pickObject(SIDE_A_ID);
		// 2. pick second batch from alpha
		movement.setSide(SIDE_BC);
		movement.goBack(100, lidar);
		movement.setSide(SIDE_B);
		actuators.releaseObject(SIDE_B_ID);
		movement.ExecuteSEMI(batch_alpha, lidar);
		actuators.pickObject(SIDE_B_ID);
		//
		movement.setSide(SIDE_CA);
		movement.goBack(100, lidar);
	}
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
