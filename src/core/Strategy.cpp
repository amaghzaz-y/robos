#include "Strategy.h"

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

// void Strategy::startStratA(bool *lidar)
// {
// dropAllCherries();

// 	if (team == 0)
// 	{

// 		Point2D midPoint = Point2D(1500, 725);
// 		Point2D zoneCenter0 = Point2D(1875, 225);
// 		Point2D delta1 = Point2D(PolarVec(45, 200).toVec2().A + zoneCenter0.X, PolarVec(45, 200).toVec2().B + zoneCenter0.Y);
// 		Point2D delta2 = Point2D(PolarVec(45, -200).toVec2().A + zoneCenter0.X, PolarVec(45, -200).toVec2().B + zoneCenter0.Y);
// 		// try this if delta2 is fucked
// 		// Point2D delta2 = Point2D(PolarVec(225, 200).toVec2().A + zoneCenter0.X, PolarVec(225, 200).toVec2().B + zoneCenter0.Y);

// 		//***************************
// 		// Picking up the first Tres
// 		//***************************
// 		actuators.releaseObject(SIDE_A_ID);
// 		movement.ExecuteSEMIOFFSET(Point2D(575, 225), lidar);
// 		actuators.delevateObject(SIDE_A_ID, 0);
// 		actuators.pickObject(SIDE_A_ID);
// 		actuators.elevateObject(SIDE_A_ID, 2);

// 		movement.setSide(SIDE_B);
// 		actuators.releaseObject(SIDE_B_ID);
// 		movement.ExecuteSEMIOFFSET(Point2D(775, 225), lidar);
// 		actuators.delevateObject(SIDE_B_ID, 0);
// 		actuators.pickObject(SIDE_B_ID);
// 		actuators.elevateObject(SIDE_B_ID, 2);

// 		movement.setSide(SIDE_C);
// 		actuators.releaseObject(SIDE_C_ID);
// 		movement.ExecuteSEMIOFFSET(Point2D(1125, 725), lidar);
// 		actuators.delevateObject(SIDE_C_ID, 0);
// 		actuators.pickObject(SIDE_C_ID);
// 		actuators.elevateObject(SIDE_C_ID, 2);

// 		// put side C
// 		movement.ExecuteSEMI(midPoint, lidar);
// 		movement.ExecuteSEMI(delta1, lidar);
// 		actuators.delevateObject(SIDE_C_ID, 0);
// 		actuators.releaseObject(SIDE_C_ID);
// 		actuators.elevateObject(SIDE_C_ID, 1);

// 		// put side B
// 		movement.setSide(SIDE_AB);
// 		movement.ExecuteSEMI(delta2, lidar);
// 		movement.setSide(SIDE_B);
// 		movement.ExecuteSEMI(zoneCenter0, lidar);
// 		actuators.delevateObject(SIDE_B_ID, 0);
// 		actuators.releaseObject(SIDE_B_ID);
// 		actuators.elevateObject(SIDE_B_ID, 1);

// 		// put side A
// 		movement.setSide(SIDE_CA);
// 		movement.ExecuteSEMI(midPoint, lidar);
// 		movement.setSide(SIDE_A);
// 		movement.ExecuteSEMI(delta2, lidar);
// 		actuators.delevateObject(SIDE_A_ID, 0);
// 		actuators.releaseObject(SIDE_A_ID);
// 		actuators.elevateObject(SIDE_A_ID, 1);
// 		// return to midpoint
// 		movement.setSide(SIDE_BC);
// 		movement.ExecuteSEMI(midPoint, lidar);
// 		//**************************
// 		// GO CLOSEST HOME
// 		//***********************
// 		movement.setSide(SIDE_A);
// 		movement.ExecuteSEMI(Point2D(225, 225), lidar);
// 		//**************************
// 		// Picking up the 2nd Tres
// 		//**************************

// 		// movement.FullStop();
// 	}
// 	else if (team == 1)
// 	{
// 		Point2D midPoint = Point2D(1500, 1225);
// 		Point2D zoneCenter0 = Point2D(1875, 1775);
// 		Point2D delta1 = Point2D(1650, 1550);
// 		Point2D delta2 = Point2D(2100, 1750);
// 		// try this if delta2 is fucked
// 		// Point2D delta2 = Point2D(PolarVec(225, 200).toVec2().A + zoneCenter0.X, PolarVec(225, 200).toVec2().B + zoneCenter0.Y)
// 		//***************************z
// 		// Picking up the first Tres
// 		//***************************
// 		actuators.releaseObject(SIDE_A_ID);
// 		movement.ExecuteSEMIOFFSET(Point2D(575, 1775), lidar);
// 		actuators.delevateObject(SIDE_A_ID, 0);
// 		actuators.pickObject(SIDE_A_ID);
// 		actuators.elevateObject(SIDE_A_ID, 2);

// 		movement.setSide(SIDE_B);
// 		actuators.releaseObject(SIDE_B_ID);
// 		movement.ExecuteSEMIOFFSET(Point2D(775, 1775), lidar);
// 		actuators.delevateObject(SIDE_B_ID, 0);
// 		actuators.pickObject(SIDE_B_ID);
// 		actuators.elevateObject(SIDE_B_ID, 2);

// 		movement.setSide(SIDE_C);
// 		actuators.releaseObject(SIDE_C_ID);
// 		movement.ExecuteSEMIOFFSET(Point2D(1125, 1275), lidar);
// 		actuators.delevateObject(SIDE_C_ID, 0);
// 		actuators.pickObject(SIDE_C_ID);
// 		actuators.elevateObject(SIDE_C_ID, 2);

// 		// put side C
// 		movement.ExecuteSEMI(midPoint, lidar);
// 		movement.ExecuteSEMI(delta1, lidar);
// 		actuators.delevateObject(SIDE_C_ID, 0);
// 		actuators.releaseObject(SIDE_C_ID);
// 		actuators.elevateObject(SIDE_C_ID, 1);

// 		// put side B
// 		movement.setSide(SIDE_AB);
// 		movement.ExecuteSEMI(delta2, lidar);
// 		movement.setSide(SIDE_B);
// 		movement.ExecuteSEMI(zoneCenter0, lidar);
// 		actuators.delevateObject(SIDE_B_ID, 0);
// 		actuators.releaseObject(SIDE_B_ID);
// 		actuators.elevateObject(SIDE_B_ID, 1);

// 		// put side A
// 		movement.setSide(SIDE_CA);
// 		movement.ExecuteSEMI(midPoint, lidar);
// 		movement.setSide(SIDE_A);
// 		movement.ExecuteSEMI(delta2, lidar);
// 		actuators.delevateObject(SIDE_A_ID, 0);
// 		actuators.releaseObject(SIDE_A_ID);
// 		actuators.elevateObject(SIDE_A_ID, 1);
// 		// return to midpoint
// 		movement.setSide(SIDE_BC);
// 		movement.ExecuteSEMI(midPoint, lidar);
// 		//**************************
// 		// GO CLOSEST HOME
// 		//**************************
// 		movement.setSide(SIDE_A);
// 		movement.ExecuteSEMI(Point2D(225, 1775), lidar);
// 	}
// }

void Strategy::startStratB(bool *lidar)
{
	dropAllCherries();

	// old value 1920
	Point2D zoneCenter0 = Point2D(2000, 1740);
	Point2D home1 = Point2D(3000, 1400);
	Point2D midPoint0 = Point2D(775, 1285);
	Point2D delta0 = Point2D(2000, 1490);
	Point2D delta1 = Point2D(2000, 1540);
	Point2D delta2 = Point2D(2000, 1640);
	Point2D pink0 = Point2D(575, 1775);
	Point2D yellow0 = Point2D(775, 1775);
	Point2D brown0 = Point2D(1125, 1275);
	// for green
	Point2D zoneCenter0_GREEN = Point2D(2000, 260);
	Point2D home1_GREEN = Point2D(3000, 900);
	Point2D midPoint0_GREEN = Point2D(775, 715);
	Point2D delta0_GREEN = Point2D(2000, 510);
	Point2D delta1_GREEN = Point2D(2000, 460);
	Point2D delta2_GREEN = Point2D(2000, 360);
	Point2D pink0_GREEN = Point2D(575, 225);
	Point2D yellow0_GREEN = Point2D(775, 225);
	Point2D brown0_GREEN = Point2D(1125, 725);
	if (team == 1)
	{
		//***************************
		// Picking up the first Tres
		//***************************
		// picking pink with A
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(pink0, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 2);

		// picking yellow with C
		movement.setSide(SIDE_C);
		actuators.releaseObject(SIDE_C_ID);
		movement.ExecuteSEMIOFFSET(yellow0, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.pickObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 2);
		// translate to MidPoint 0
		movement.Execute(midPoint0, lidar);
		// picking brown with B
		movement.setSide(SIDE_B);
		actuators.releaseObject(SIDE_B_ID);
		movement.ExecuteSEMIOFFSET(brown0, lidar);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.pickObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_B_ID, 3);

		// go to delta0
		movement.ExecuteSEMI(delta0, lidar);
		// deposit pink and yellow at center
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(zoneCenter0, lidar);
		actuators.dropCherry();
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.releaseObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		// deposit brown at delta1
		movement.setSide(SIDE_C);
		movement.ExecuteSEMI(delta0, lidar);
		movement.ExecuteSEMI(delta1, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.releaseObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		movement.ExecuteSEMI(delta2, lidar);
		// return to delta0
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(delta0, lidar);
		//**************************
		// GO CLOSEST HOME
		//***********************
		movement.ExecuteSEMI(home1, lidar);
	}
	else if (team == 0)
	{
		//***************************
		// Picking up the first Tres
		//***************************
		// picking pink with A
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(pink0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 2);

		// picking yellow with C
		movement.setSide(SIDE_B);
		actuators.releaseObject(SIDE_B_ID);
		movement.ExecuteSEMIOFFSET(yellow0_GREEN, lidar);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.pickObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_B_ID, 2);
		// translate to MidPoint 0
		movement.Execute(midPoint0_GREEN, lidar);
		// picking brown with B
		movement.setSide(SIDE_C);
		actuators.releaseObject(SIDE_C_ID);
		movement.ExecuteSEMIOFFSET(brown0_GREEN, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.pickObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		actuators.dropCherry();
		// go to delta0
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		// deposit pink and yellow at center
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(zoneCenter0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.releaseObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		// deposit brown at delta1
		movement.setSide(SIDE_C);
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		movement.ExecuteSEMI(delta1_GREEN, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.releaseObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		movement.ExecuteSEMI(delta2_GREEN, lidar);
		// return to delta0
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		//**************************
		// GO CLOSEST HOME
		//***********************
		movement.ExecuteSEMI(home1_GREEN, lidar);
	}
}

void Strategy::dropAllCherries()
{
	actuators.dropCherryStream();
	delay(2000);
	movement.rotateTo(SIDE_CA);
	movement.runSync();
}

void Strategy::startStratC(bool *lidar)
{
	dropAllCherries();
	Point2D zoneCenter0 = Point2D(2000, 1740);
	Point2D home1 = Point2D(2900, 1200);
	Point2D midPoint0 = Point2D(775, 1285);
	Point2D delta0 = Point2D(2000, 1490);
	Point2D delta1 = Point2D(2000, 1540);
	Point2D delta2 = Point2D(2000, 1640);
	Point2D pink0 = Point2D(575, 1775);
	Point2D yellow0 = Point2D(775, 1775);
	Point2D brown0 = Point2D(1125, 1275);
	// for green
	Point2D zoneCenter0_GREEN = Point2D(2000, 260);
	Point2D home1_GREEN = Point2D(2900, 800);
	Point2D midPoint0_GREEN = Point2D(775, 715);
	Point2D delta0_GREEN = Point2D(2000, 510);
	Point2D delta1_GREEN = Point2D(2000, 460);
	Point2D delta2_GREEN = Point2D(2000, 360);
	Point2D pink0_GREEN = Point2D(575, 225);
	Point2D yellow0_GREEN = Point2D(775, 225);
	Point2D brown0_GREEN = Point2D(1125, 725);
	if (team == 1)
	{
		//***************************
		// Picking up the first Tres
		//***************************
		// picking pink with A
		movement.setSide(SIDE_A);
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(pink0, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);

		// picking yellow with C
		movement.setSide(SIDE_C);
		actuators.releaseObject(SIDE_C_ID);
		movement.ExecuteSEMIOFFSET(yellow0, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.pickObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		// translate to MidPoint 0
		movement.Execute(midPoint0, lidar);
		// picking brown with B
		movement.setSide(SIDE_B);
		actuators.releaseObject(SIDE_B_ID);
		movement.ExecuteSEMIOFFSET(brown0, lidar);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.pickObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_B_ID, 3);
		actuators.dropCherry();
		// delay(100);
		// go to delta0
		movement.ExecuteSEMI(delta0, lidar);
		// deposit pink and yellow at center
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(zoneCenter0, lidar);

		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.releaseObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		// deposit brown at delta1
		movement.setSide(SIDE_C);
		movement.ExecuteSEMI(delta0, lidar);
		movement.ExecuteSEMI(delta1, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.releaseObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		movement.ExecuteSEMI(delta2, lidar);
		// return to delta0
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(delta0, lidar);
		//**************************
		// GO CLOSEST HOME
		//***********************
		movement.ExecuteSEMI(home1, lidar);
	}
	else if (team == 0)
	{
		//***************************
		// Picking up the first Tres
		//***************************
		// picking pink with A
		movement.setSide(SIDE_A);
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(pink0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);

		// picking yellow with C
		movement.setSide(SIDE_B);
		actuators.releaseObject(SIDE_B_ID);
		movement.ExecuteSEMIOFFSET(yellow0_GREEN, lidar);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.pickObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_B_ID, 3);
		// translate to MidPoint 0
		movement.Execute(midPoint0_GREEN, lidar);
		// picking brown with B
		movement.setSide(SIDE_C);
		actuators.releaseObject(SIDE_C_ID);
		movement.ExecuteSEMIOFFSET(brown0_GREEN, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.pickObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		actuators.dropCherry();
		// delay(100);

		// go to delta0
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		// deposit pink and yellow at center
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(zoneCenter0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.releaseObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		// deposit brown at delta1
		movement.setSide(SIDE_C);
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		movement.ExecuteSEMI(delta1_GREEN, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.releaseObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		movement.ExecuteSEMI(delta2_GREEN, lidar);
		// return to delta0
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		//**************************
		// GO CLOSEST HOME
		//***********************
		movement.ExecuteSEMI(home1_GREEN, lidar);
	}
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
void Strategy::startStratD(bool *lidar)
{
	dropAllCherries();
	Point2D zoneCenter0 = Point2D(2000, 1800);
	Point2D home1 = Point2D(2900, 1200);
	Point2D midPoint0 = Point2D(775, 1285);
	Point2D alpha0 = Point2D(280, 1775);
	Point2D alpha1 = Point2D(450, 1775);
	Point2D delta0 = Point2D(2000, 1490);
	Point2D delta1 = Point2D(2000, 1540);
	Point2D delta2 = Point2D(2000, 1640);
	Point2D pink0 = Point2D(575, 1775);
	Point2D yellow0 = Point2D(775, 1775);
	Point2D brown0 = Point2D(1125, 1275);
	Point2D brown1 = Point2D(1875, 1275);

	// for green
	Point2D zoneCenter0_GREEN = Point2D(2000, 200);
	Point2D home1_GREEN = Point2D(2900, 800);
	Point2D midPoint0_GREEN = Point2D(775, 715);
	Point2D alpha0_GREEN = Point2D(280, 225);
	Point2D alpha1_GREEN = Point2D(450, 225);
	Point2D delta0_GREEN = Point2D(2000, 510);
	Point2D delta1_GREEN = Point2D(2000, 410);
	Point2D delta2_GREEN = Point2D(2000, 310);
	Point2D pink0_GREEN = Point2D(575, 225);
	Point2D yellow0_GREEN = Point2D(775, 225);
	Point2D brown0_GREEN = Point2D(1125, 725);
	Point2D brown1_GREEN = Point2D(1875, 725);

	// Point2D zoneCenter0 = Point2D(2000, 1740);
	// Point2D home1 = Point2D(2900, 1200);
	// Point2D midPoint0 = Point2D(775, 1285);
	// Point2D delta0 = Point2D(2000, 1490);
	// Point2D delta1 = Point2D(2000, 1540);
	// Point2D delta2 = Point2D(2000, 1640);
	// Point2D pink0 = Point2D(575, 1775);
	// Point2D yellow0 = Point2D(775, 1775);
	// Point2D brown0 = Point2D(1125, 1275);
	// // for green
	// Point2D zoneCenter0_GREEN = Point2D(2000, 260);
	// Point2D home1_GREEN = Point2D(2900, 800);
	// Point2D midPoint0_GREEN = Point2D(775, 715);
	// Point2D delta0_GREEN = Point2D(2000, 510);
	// Point2D delta1_GREEN = Point2D(2000, 460);
	// Point2D delta2_GREEN = Point2D(2000, 360);
	// Point2D pink0_GREEN = Point2D(575, 225);
	// Point2D yellow0_GREEN = Point2D(775, 225);
	// Point2D brown0_GREEN = Point2D(1125, 725);
	if (team == 1)
	{
		//***************************
		// Picking up the first Tres
		//***************************
		// picking pink with A
		movement.setSide(SIDE_A);
		movement.Execute(Point2D(225, 1800), lidar); // 1775
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(pink0, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);

		// drop pink0
		movement.ExecuteSEMI(alpha0, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 2);
		// goint to alpha1
		movement.setSide(SIDE_BC);
		movement.ExecuteSEMI(alpha1, lidar);
		// picking yellow with C
		movement.setSide(SIDE_C);
		actuators.releaseObject(SIDE_C_ID);
		movement.ExecuteSEMIOFFSET(yellow0, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.pickObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		// translate to MidPoint 0
		movement.Execute(midPoint0, lidar);
		// picking brown with B
		movement.setSide(SIDE_A);
		actuators.delevateObject(SIDE_A_ID, 0);

		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(brown0, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		// picking brown1 with A
		movement.setSide(SIDE_B);
		actuators.releaseObject(SIDE_B_ID);
		movement.ExecuteSEMIOFFSET(brown1, lidar);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.pickObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_B_ID, 3);
		actuators.dropCherry();
		// delay(100);
		// go to delta0
		movement.ExecuteSEMI(delta0, lidar);
		// deposit pink and yellow at center
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(zoneCenter0, lidar);

		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.releaseObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		// deposit brown at delta1
		movement.setSide(SIDE_C);
		movement.ExecuteSEMI(delta0, lidar);
		movement.ExecuteSEMI(delta1, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.releaseObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);

		movement.ExecuteSEMI(delta2, lidar);
		// return to delta0
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(delta0, lidar);
		//**************************
		// GO CLOSEST HOME
		//***********************
		movement.ExecuteSEMI(home1, lidar);
	}
	else if (team == 0)
	{
		//***************************
		// Picking up the first Tres
		//***************************
		// picking pink with A
		movement.setSide(SIDE_A);
		movement.Execute(Point2D(225, 225), lidar);
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(pink0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);

		// drop pink0
		movement.ExecuteSEMI(alpha0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 2);
		// goint to alpha1
		movement.setSide(SIDE_BC);
		movement.ExecuteSEMI(alpha1_GREEN, lidar);
		// picking yellow with C
		movement.setSide(SIDE_B);
		actuators.releaseObject(SIDE_B_ID);
		movement.ExecuteSEMIOFFSET(yellow0_GREEN, lidar);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.pickObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_B_ID, 3);
		// translate to MidPoint 0
		movement.Execute(midPoint0_GREEN, lidar);
		// picking brown with B
		movement.setSide(SIDE_A);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(brown0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		// picking brown1 with A
		movement.setSide(SIDE_C);
		actuators.releaseObject(SIDE_C_ID);
		movement.ExecuteSEMIOFFSET(brown1_GREEN, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.pickObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		actuators.dropCherry();
		// delay(100);
		// go to delta0
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		// deposit pink and yellow at center
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(zoneCenter0_GREEN, lidar);

		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.releaseObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		// deposit brown at delta1
		movement.setSide(SIDE_C);
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		movement.ExecuteSEMI(delta1_GREEN, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.releaseObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);

		movement.ExecuteSEMI(delta2_GREEN, lidar);
		// return to delta0
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		//**************************
		// GO CLOSEST HOME
		//***********************
		movement.ExecuteSEMI(home1_GREEN, lidar);
	}
}

void Strategy::Demo1(bool *lidar)
{
	// for blue
	// dropAllCherries();
	Point2D zoneCenter0 = Point2D(1125, 225);
	Point2D home1 = Point2D(225, 1775);
	Point2D alpha0 = Point2D(280, 1775);
	Point2D alpha1 = Point2D(450, 1775);
	// increase X of deltas to increase offset
	Point2D delta0 = Point2D(1200, 510); // 1125
	Point2D delta1 = Point2D(1200, 410);
	Point2D delta2 = Point2D(1200, 310);

	Point2D pink0 = Point2D(575, 1775);
	Point2D yellow0 = Point2D(775, 1775);
	Point2D brown0 = Point2D(1125, 1275);
	Point2D brown1 = Point2D(1125, 725);

	// for green
	Point2D zoneCenter0_GREEN = Point2D(1125, 1775);
	Point2D home1_GREEN = Point2D(225, 225);
	Point2D alpha0_GREEN = Point2D(280, 225);
	Point2D alpha1_GREEN = Point2D(450, 225);
	Point2D delta0_GREEN = Point2D(1200, 1490);
	Point2D delta1_GREEN = Point2D(1200, 1590);
	Point2D delta2_GREEN = Point2D(1200, 1690);
	Point2D pink0_GREEN = Point2D(575, 225);
	Point2D yellow0_GREEN = Point2D(775, 225);
	Point2D brown0_GREEN = Point2D(1125, 725);
	Point2D brown1_GREEN = Point2D(1125, 1275);

	if (team == 1)
	{
		//***************************
		// Picking up the first Tres
		//***************************
		// picking pink with A
		movement.setSide(SIDE_A);
		movement.Execute(Point2D(225, 1800), lidar); // 1775
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(pink0, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);

		// drop pink0
		movement.ExecuteSEMI(alpha0, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 2);
		// goint to alpha1
		movement.setSide(SIDE_BC);
		movement.ExecuteSEMI(alpha1, lidar);
		// picking yellow with C
		movement.setSide(SIDE_C);
		actuators.releaseObject(SIDE_C_ID);
		movement.ExecuteSEMIOFFSET(yellow0, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.pickObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		// translate to MidPoint 0
		// picking brown with A
		movement.setSide(SIDE_A);
		actuators.delevateObject(SIDE_A_ID, 0);

		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(brown0, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		// picking brown1 with B
		movement.setSide(SIDE_B);
		actuators.releaseObject(SIDE_B_ID);
		movement.ExecuteSEMIOFFSET(brown1, lidar);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.pickObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_B_ID, 3);
		actuators.dropCherry();
		// go to delta0
		movement.ExecuteSEMI(delta0, lidar);
		// deposit pink and yellow at center
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(zoneCenter0, lidar);

		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.releaseObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		// deposit brown at delta1
		movement.setSide(SIDE_C);
		// movement.ExecuteSEMI(delta0, lidar);
		movement.ExecuteSEMI(delta1, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.releaseObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		// push cake C
		movement.ExecuteSEMI(delta2, lidar);
		// return to delta0
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(delta0, lidar);
		//**************************
		// GO CLOSEST HOME
		//***********************
		movement.ExecuteSEMI(home1, lidar);
	}
	else if (team == 0)
	{
		//***************************
		// Picking up the first Tres
		//***************************
		// picking pink with A
		movement.setSide(SIDE_A);
		movement.Execute(Point2D(225, 225), lidar);
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(pink0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);

		// drop pink0
		movement.ExecuteSEMI(alpha0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 2);
		// goint to alpha1
		movement.setSide(SIDE_BC);
		movement.ExecuteSEMI(alpha1_GREEN, lidar);
		// picking yellow with C
		movement.setSide(SIDE_B);
		actuators.releaseObject(SIDE_B_ID);
		movement.ExecuteSEMIOFFSET(yellow0_GREEN, lidar);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.pickObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_B_ID, 3);
		// picking brown with A
		movement.setSide(SIDE_A);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(brown0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		// picking brown1 with C
		movement.setSide(SIDE_C);
		actuators.releaseObject(SIDE_C_ID);
		movement.ExecuteSEMIOFFSET(brown1_GREEN, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.pickObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		actuators.dropCherry();
		// delay(100);
		// go to delta0
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		// deposit pink and yellow at center
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(zoneCenter0_GREEN, lidar);

		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.releaseObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		// deposit brown at delta1
		movement.setSide(SIDE_C);
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		movement.ExecuteSEMI(delta1_GREEN, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.releaseObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);

		movement.ExecuteSEMI(delta2_GREEN, lidar);
		// return to delta0
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		//**************************
		// GO CLOSEST HOME
		//***********************
		movement.ExecuteSEMI(home1_GREEN, lidar);
	}
}

void Strategy::Demo2(bool *lidar)
{
	// for blue
	// dropAllCherries();
	Point2D zoneCenter0 = Point2D(1125, 225);
	Point2D home1 = Point2D(225, 1775);
	Point2D alpha0 = Point2D(280, 1775);
	Point2D alpha1 = Point2D(450, 1775);
	// increase X of deltas to increase offset
	Point2D delta0 = Point2D(1125, 510);
	Point2D delta1 = Point2D(1125, 410);
	Point2D delta2 = Point2D(1125, 310);

	Point2D pink0 = Point2D(575, 1775);
	Point2D yellow0 = Point2D(775, 1775);
	Point2D brown0 = Point2D(1125, 1275);
	Point2D brown1 = Point2D(1125, 725);

	// for green
	Point2D zoneCenter0_GREEN = Point2D(1125, 1775);
	Point2D home1_GREEN = Point2D(225, 225);
	Point2D alpha0_GREEN = Point2D(280, 225);
	Point2D alpha1_GREEN = Point2D(450, 225);
	Point2D delta0_GREEN = Point2D(1125, 1490);
	Point2D delta1_GREEN = Point2D(1125, 1590);
	Point2D delta2_GREEN = Point2D(1125, 1690);
	Point2D pink0_GREEN = Point2D(575, 225);
	Point2D yellow0_GREEN = Point2D(775, 225);
	Point2D brown0_GREEN = Point2D(1125, 725);
	Point2D brown1_GREEN = Point2D(1125, 1275);

	if (team == 1)
	{
		//***************************
		// Picking up the first Tres
		//***************************
		// picking pink with A
		movement.setSide(SIDE_A);
		movement.Execute(Point2D(225, 1800), lidar); // 1775
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(pink0, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);

		// drop pink0
		movement.ExecuteSEMI(alpha0, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 2);
		// goint to alpha1
		movement.setSide(SIDE_BC);
		movement.ExecuteSEMI(alpha1, lidar);
		// picking yellow with C
		movement.setSide(SIDE_C);
		actuators.releaseObject(SIDE_C_ID);
		movement.ExecuteSEMIOFFSET(yellow0, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.pickObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		// translate to MidPoint 0
		// picking brown with A
		movement.setSide(SIDE_A);
		actuators.delevateObject(SIDE_A_ID, 0);

		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(brown0, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		// picking brown1 with B
		movement.setSide(SIDE_B);
		actuators.releaseObject(SIDE_B_ID);
		movement.ExecuteSEMIOFFSET(brown1, lidar);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.pickObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_B_ID, 3);
		actuators.dropCherry();
		// go to delta0
		movement.ExecuteSEMI(delta0, lidar);
		// deposit pink and yellow at center
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(zoneCenter0, lidar);

		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.releaseObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		// deposit brown at delta1
		movement.setSide(SIDE_C);
		// movement.ExecuteSEMI(delta0, lidar);
		movement.ExecuteSEMI(delta1, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.releaseObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		// push cake C
		movement.ExecuteSEMI(delta2, lidar);
		// return to delta0
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(delta0, lidar);
		//**************************
		// GO CLOSEST HOME
		//***********************
		movement.ExecuteSEMI(home1, lidar);
	}
	else if (team == 0)
	{
		//***************************
		// Picking up the first Tres
		//***************************
		// picking pink with A
		movement.setSide(SIDE_A);
		movement.Execute(Point2D(225, 225), lidar);
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(pink0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);

		// drop pink0
		movement.ExecuteSEMI(alpha0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 2);
		// goint to alpha1
		movement.setSide(SIDE_BC);
		movement.ExecuteSEMI(alpha1_GREEN, lidar);
		// picking yellow with C
		movement.setSide(SIDE_B);
		actuators.releaseObject(SIDE_B_ID);
		movement.ExecuteSEMIOFFSET(yellow0_GREEN, lidar);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.pickObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_B_ID, 3);
		// picking brown with A
		movement.setSide(SIDE_A);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		movement.ExecuteSEMIOFFSET(brown0_GREEN, lidar);
		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.pickObject(SIDE_A_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		// picking brown1 with C
		movement.setSide(SIDE_C);
		actuators.releaseObject(SIDE_C_ID);
		movement.ExecuteSEMIOFFSET(brown1_GREEN, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.pickObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);
		actuators.dropCherry();
		// delay(100);
		// go to delta0
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		// deposit pink and yellow at center
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(zoneCenter0_GREEN, lidar);

		actuators.delevateObject(SIDE_A_ID, 0);
		actuators.delevateObject(SIDE_B_ID, 0);
		actuators.releaseObject(SIDE_A_ID);
		actuators.releaseObject(SIDE_B_ID);
		actuators.elevateObject(SIDE_A_ID, 3);
		actuators.elevateObject(SIDE_B_ID, 3);
		// deposit brown at delta1
		movement.setSide(SIDE_C);
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		movement.ExecuteSEMI(delta1_GREEN, lidar);
		actuators.delevateObject(SIDE_C_ID, 0);
		actuators.releaseObject(SIDE_C_ID);
		actuators.elevateObject(SIDE_C_ID, 3);

		movement.ExecuteSEMI(delta2_GREEN, lidar);
		// return to delta0
		movement.setSide(SIDE_AB);
		movement.ExecuteSEMI(delta0_GREEN, lidar);
		//**************************
		// GO CLOSEST HOME
		//***********************
		movement.ExecuteSEMI(home1_GREEN, lidar);
	}
}
void Strategy::cookMeth(bool *lidar)
{
	// Points of interest
	// Point2D entryPoint = Point2D(0, 0);
	Point2D zoneCenter = Point2D(725, 1000);
	Point2D delta0 = Point2D(PolarVec(0, 200).toVec2().A + zoneCenter.X, PolarVec(0, 200).toVec2().B + zoneCenter.Y);
	Point2D delta1 = Point2D(PolarVec(90, 200).toVec2().A + zoneCenter.X, PolarVec(90, 200).toVec2().B + zoneCenter.Y);
	Point2D delta2 = Point2D(PolarVec(-180, 200).toVec2().A + zoneCenter.X, PolarVec(-180, 200).toVec2().B + zoneCenter.Y);
	// Dropping first brown part, IMPORTANT side A facing north !!!
	// movement.setCurrentPosition(entryPoint);
	// ----------------------------------
	// making the first cake @ delta0 //
	// ----------------------------------
	movement.setSide(SIDE_C);
	actuators.elevateObject(SIDE_C_ID, 2);
	movement.ExecuteSEMI(delta0, lidar);
	actuators.delevateObject(SIDE_C_ID, 0);
	actuators.releaseObject(SIDE_C_ID);
	// picking rest brown parts
	actuators.elevateObject(SIDE_C_ID, 1);
	actuators.pickObject(SIDE_C_ID);
	// Return to center
	movement.setSide(SIDE_AB);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// dropping first yellow part
	actuators.elevateObject(SIDE_B_ID, 3);
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(delta0, lidar);
	actuators.delevateObject(SIDE_B_ID, 1);
	actuators.releaseObject(SIDE_B_ID);
	// picking rest yellow parts
	actuators.elevateObject(SIDE_B_ID, 2);
	actuators.pickObject(SIDE_B_ID);
	// Return to center
	movement.setSide(SIDE_CA);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// dropping first pink part
	actuators.elevateObject(SIDE_A_ID, 3);
	movement.setSide(SIDE_A);
	movement.ExecuteSEMI(delta0, lidar);
	actuators.delevateObject(SIDE_A_ID, 2);
	actuators.releaseObject(SIDE_A_ID);
	// picking rest pink parts	// Return to center
	actuators.elevateObject(SIDE_A_ID, 3);
	actuators.pickObject(SIDE_A_ID);
	// Return to center
	movement.setSide(SIDE_BC);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// ----------------------------------
	// making the second cake @ delta1 //
	// ----------------------------------
	movement.setSide(SIDE_C);
	actuators.elevateObject(SIDE_C_ID, 2);
	movement.ExecuteSEMI(delta1, lidar);
	// drop the second brown cake
	actuators.delevateObject(SIDE_C_ID, 0);
	actuators.releaseObject(SIDE_C_ID);
	// pickup the rest
	actuators.elevateObject(SIDE_C_ID, 1);
	actuators.pickObject(SIDE_C_ID);
	// return to center
	movement.setSide(SIDE_AB);
	movement.ExecuteSEMIOFFSET(zoneCenter, lidar);
	// drop the yellow cake
	actuators.elevateObject(SIDE_B_ID, 3);
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(delta1, lidar);
	actuators.delevateObject(SIDE_B_ID, 1);
	actuators.releaseObject(SIDE_B_ID);
	// pick the rest
	actuators.elevateObject(SIDE_B_ID, 2);
	actuators.pickObject(SIDE_B_ID);
	// return to center
	movement.setSide(SIDE_CA);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// drop the pink cake
	actuators.elevateObject(SIDE_A_ID, 3);
	movement.setSide(SIDE_A);
	movement.ExecuteSEMI(delta1, lidar);
	actuators.delevateObject(SIDE_A_ID, 2);
	actuators.releaseObject(SIDE_A_ID);
	actuators.elevateObject(SIDE_A_ID, 3);
	actuators.pickObject(SIDE_A_ID);
	// return to center
	movement.setSide(SIDE_BC);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// ----------------------------------
	// making the third cake @ delta2 //
	// ----------------------------------
	// putting the third brown cake
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(delta2, lidar);
	actuators.delevateObject(SIDE_C_ID, 0);
	actuators.releaseObject(SIDE_C_ID);
	// return to center
	movement.setSide(SIDE_AB);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// drop the third yellow cake
	movement.setSide(SIDE_B);
	actuators.elevateObject(SIDE_B_ID, 2);
	movement.ExecuteSEMI(delta2, lidar);
	actuators.delevateObject(SIDE_B_ID, 1);
	actuators.releaseObject(SIDE_B_ID);
	// return to center
	movement.setSide(SIDE_CA);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// dropping the last pink cake
	movement.setSide(SIDE_A);
	actuators.elevateObject(SIDE_A_ID, 3);
	movement.ExecuteSEMI(delta2, lidar);
	actuators.delevateObject(SIDE_A_ID, 2);
	actuators.releaseObject(SIDE_A_ID);
	actuators.elevateObject(SIDE_A_ID, 3);
	// return to center
	movement.setSide(SIDE_BC);
	movement.ExecuteSEMI(zoneCenter, lidar);
}

// void Strategy::cookMeth(bool *lidar)
// {
// 	// Points of interest
// 	// Point2D entryPoint = Point2D(0, 0);
// 	Point2D zoneCenter = Point2D(500, 500);
// 	Point2D delta0 = Point2D(PolarVec(0, 200).toVec2().A + zoneCenter.X, PolarVec(0, 200).toVec2().B + zoneCenter.Y);
// 	Point2D delta1 = Point2D(PolarVec(90, 200).toVec2().A + zoneCenter.X, PolarVec(90, 200).toVec2().B + zoneCenter.Y);
// 	Point2D delta2 = Point2D(PolarVec(-180, 200).toVec2().A + zoneCenter.X, PolarVec(-180, 200).toVec2().B + zoneCenter.Y);
// 	// Dropping first brown part, IMPORTANT side A facing north !!!
// 	// movement.setCurrentPosition(entryPoint);
// 	// ----------------------------------
// 	// making the first cake @ delta0 //
// 	// ----------------------------------
// 	movement.setSide(SIDE_C);
// 	actuators.elevateObject(SIDE_C_ID, 2);
// 	movement.ExecuteSEMIOFFSET(delta0, lidar);
// 	actuators.delevateObject(SIDE_C_ID, 0);
// 	actuators.releaseObject(SIDE_C_ID);
// 	// picking rest brown parts
// 	actuators.elevateObject(SIDE_C_ID, 1);
// 	actuators.pickObject(SIDE_C_ID);
// 	// Return to center
// 	movement.setSide(SIDE_AB);
// 	movement.ExecuteSEMI(zoneCenter, lidar);
// 	// dropping first yellow part
// 	actuators.elevateObject(SIDE_B_ID, 3);
// 	movement.setSide(SIDE_B);
// 	movement.ExecuteSEMI(delta0, lidar);
// 	actuators.delevateObject(SIDE_B_ID, 1);
// 	actuators.releaseObject(SIDE_B_ID);
// 	// picking rest yellow parts
// 	actuators.elevateObject(SIDE_B_ID, 2);
// 	actuators.pickObject(SIDE_B_ID);
// 	// Return to center
// 	movement.setSide(SIDE_CA);
// 	movement.ExecuteSEMI(zoneCenter, lidar);
// 	// dropping first pink part
// 	actuators.elevateObject(SIDE_A_ID, 3);
// 	movement.setSide(SIDE_A);
// 	movement.ExecuteSEMI(delta0, lidar);
// 	actuators.delevateObject(SIDE_A_ID, 2);
// 	actuators.releaseObject(SIDE_A_ID);
// 	// picking rest pink parts	// Return to center
// 	actuators.elevateObject(SIDE_A_ID, 3);
// 	actuators.pickObject(SIDE_A_ID);
// 	// Return to center
// 	movement.setSide(SIDE_BC);
// 	movement.ExecuteSEMIOFFSET(zoneCenter, lidar);
// 	// ----------------------------------
// 	// making the second cake @ delta1 //
// 	// ----------------------------------
// 	movement.setSide(SIDE_C);
// 	actuators.elevateObject(SIDE_C_ID, 2);
// 	movement.ExecuteSEMI(delta1, lidar);
// 	// drop the second brown cake
// 	actuators.delevateObject(SIDE_C_ID, 0);
// 	actuators.releaseObject(SIDE_C_ID);
// 	// pickup the rest
// 	actuators.elevateObject(SIDE_C_ID, 1);
// 	actuators.pickObject(SIDE_C_ID);
// 	// return to center
// 	movement.setSide(SIDE_AB);
// 	movement.ExecuteSEMIOFFSET(zoneCenter, lidar);
// 	// drop the yellow cake
// 	actuators.elevateObject(SIDE_B_ID, 3);
// 	movement.setSide(SIDE_B);
// 	movement.ExecuteSEMI(delta1, lidar);
// 	actuators.delevateObject(SIDE_B_ID, 1);
// 	actuators.releaseObject(SIDE_B_ID);
// 	// pick the rest
// 	actuators.elevateObject(SIDE_B_ID, 2);
// 	actuators.pickObject(SIDE_B_ID);
// 	// return to center
// 	movement.setSide(SIDE_CA);
// 	movement.ExecuteSEMI(zoneCenter, lidar);
// 	// drop the pink cake
// 	actuators.elevateObject(SIDE_A_ID, 3);
// 	movement.setSide(SIDE_A);
// 	movement.ExecuteSEMI(delta1, lidar);
// 	actuators.delevateObject(SIDE_A_ID, 2);
// 	actuators.releaseObject(SIDE_A_ID);
// 	actuators.elevateObject(SIDE_A_ID, 3);
// 	actuators.pickObject(SIDE_A_ID);
// 	// return to center
// 	movement.setSide(SIDE_BC);
// 	movement.ExecuteSEMI(zoneCenter, lidar);
// 	// ----------------------------------
// 	// making the third cake @ delta2 //
// 	// ----------------------------------
// 	// putting the third brown cake
// 	movement.setSide(SIDE_C);
// 	movement.ExecuteSEMI(delta2, lidar);
// 	actuators.delevateObject(SIDE_C_ID, 0);
// 	actuators.releaseObject(SIDE_C_ID);
// 	// return to center
// 	movement.setSide(SIDE_AB);
// 	movement.ExecuteSEMI(zoneCenter, lidar);
// 	// drop the third yellow cake
// 	movement.setSide(SIDE_B);
// 	actuators.elevateObject(SIDE_B_ID, 2);
// 	movement.ExecuteSEMI(delta2, lidar);
// 	actuators.delevateObject(SIDE_B_ID, 1);
// 	actuators.releaseObject(SIDE_B_ID);
// 	// return to center
// 	movement.setSide(SIDE_CA);
// 	movement.ExecuteSEMI(zoneCenter, lidar);
// 	// dropping the last pink cake
// 	movement.setSide(SIDE_A);
// 	actuators.elevateObject(SIDE_A_ID, 3);
// 	movement.ExecuteSEMI(delta2, lidar);
// 	actuators.delevateObject(SIDE_A_ID, 2);
// 	actuators.releaseObject(SIDE_A_ID);
// 	actuators.elevateObject(SIDE_A_ID, 3);
// 	// return to center
// 	movement.setSide(SIDE_BC);
// 	movement.ExecuteSEMI(zoneCenter, lidar);
// }

void Strategy::Homologuation(bool *lidar)
{
	Initiation();
	Ready();
	actuators.normalize();
	startStratA(lidar);
}

Point2D Strategy::getCurrentPoint()
{
	return movement.getCurrentPoint();
}
