#pragma once

#include <types/Steps.h>
#include <lib/stepper/AccelStepper.h>
#include <types/Point2D.h>
#include <utils/utils.h>
#include "utils/PINS.h"

#define MAX_SPEED 8000 // 4000
#define MAX_ACCEL 8000 // 6000

const int SIDE_A = 360;
const int SIDE_AB = 60;
const int SIDE_B = 120;
const int SIDE_BC = -180;
const int SIDE_C = -120;
const int SIDE_CA = -60;

const float OFFSET_DISTANCE = 35.0; // mm

class Movement
{
private:
	AccelStepper A1;
	AccelStepper A2;
	AccelStepper A3;
	Point2D currentPoint;
	float currentRotation;
	float targetRotation;
	float angleToDo;
	Point2D absPoint;
	Point2D targetPoint;
	bool calibrated;
	bool isHome;
	bool *isDetected;
	int team;
	float currentSideAngle;
	void goToPoint();
	void stop();
	Point2D TEAM_BLUE;
	Point2D TEAM_YELLOW;

public:
	Movement();
	double SPEED = 4000.0;
	double ACCEL = 6000.0;
	const double ACCEL_SUPER = 10000;
	void doRotation();
	void run();
	void runSync();
	void moveTo(Steps steps);
	void setPoint(Point2D point);
	void rotateTo(float angle);
	void goToPointRotate();
	void goToPoinRotateOffset();
	void goToPoinRotateOffset(int offset);
	void setRotation(float angle);
	void setSide(float angle);
	void setup();
	bool HasArrived();
	void FullStop();
	void setTeam(int t);
	bool isCalibrated();
	bool atHome();
	void Calibrate();
	// move to point with translation
	void Execute(Point2D point, bool *lidar);
	// move to point with rotation and translation
	void ExecuteSEMI(Point2D point, bool *lidar);
	// move to point with rotation and offset
	void ExecuteSEMIOFFSET(Point2D point, bool *lidar);
	void ExecuteSEMIOFFSET(Point2D point, int offset, bool *lidar);

	void goHome();
	void goHomeSEMI();
	void goBack(int distance, bool *lidar);
	void setCurrentPosition(Point2D point);
	Point2D getCurrentPoint();
	void lidarTest(bool *lidar);
	void TestGoNorth();
	void TestGoSouth();
	void TestGoWest();
	void TestGoEast();
	void TestBasic();
};