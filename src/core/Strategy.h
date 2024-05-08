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
#define HEIGHT 2000 // value in mm
#define WIDTH 1500	// value in mm
// const int PIN_IFM3 = 34;
// const int PIN_IFM2 = 36;
// const int PIN_IFM2 = 39;

const int PIN_RST_OLED = 19;
const int REED_PIN = PIN_L1;
const int INIT_PIN = PIN_L2;
const int TEAM_PIN = PIN_L3;

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
	NeoPixel neopixel;
	Sensors sensors;
	void Initiation();
	void Ready();
	void setup();
	void start(bool *lidar);
	void startDebug(bool *lidar);
	void startSEMI(bool *lidar);
	void startSEMIOFFSET(bool *lidar);
	void stop();
	void setPoints(Point2D *points, int len);
	void startStratA(bool *lidar);
	void startStratB(bool *lidar);
	void startStratC(bool *lidar);
	void startStratD(bool *lidar);
	// demo for normal strategy
	void Demo2(bool *lidar);
	void Demo1(bool *lidar);
	void cookMeth(bool *lidar);
	void afterCalibration(bool *lidar);
	void Homologuation(bool *lidar);
	Point2D getCurrentPoint();
	void testINPUT();
	void dropAllCherries();
};