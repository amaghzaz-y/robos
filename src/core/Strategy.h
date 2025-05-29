#pragma once

#include "types/Point2D.h"
#include "core/Movement.h"
#include "types/PolarVec.h"
#include "core/Lidar.h"
#include "core/Actuators.h"
#include "utils/PINS.h"
#include "core/Display.h"
#include "core/Actuators.h"
#include "core/NeoPixel.h"
#include "core/Sensors.h"

const int PIN_RST_OLED = 19;
const int INIT_PIN = PIN_L1;
const int TEAM_PIN = PIN_L2;
const int REED_PIN = PIN_L3;

class Strategy
{
private:
	Point2D *points;
	int currentInstruction;
	int arrayLength;
	void teamSelection();
	void init();
	int team;

public:
	Movement movement;
	Actuators actuators;
	Display display;
	// NeoPixel neopixel;
	// Sensors sensors;
	void Initiation();
	void Ready();
	void setup();
	void start(bool *lidar);
	void stop();
	void setPoints(Point2D *points, int len);
	void strat_BLUE(bool *lidar);
	void strat_BLUE_V2(bool *lidar);
	void strat_YELLOW(bool *lidar);
	void strat_YELLOW_V2(bool *lidar);
	void Homologuation(bool *lidar);
	Point2D getCurrentPoint();
	void testINPUT();
	// void dropAllCherries();
};