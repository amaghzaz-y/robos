#pragma once
#include <lib/rplidar/RPLidar.h>
#include <types/PolarVec.h>
#include <types/Point2D.h>
#include <utils/PINS.h>
#define LIDAR_MOTOR_SPEED 160
#define X_RANGE_MAX 1500
#define Y_RANGE_MAX 2000

class Lidar
{
public:
	void setup();
	void detect();
	bool hasDetected();
	void setAngle(float _angle);
	void setRadius(float _radius);
	void setMaxRange(float _range);
	void setCurrentPoint(Point2D *_point);
	bool Task(Point2D *currentPoint);
	Vec2 scan();

private:
	RPLidar lidar;
	float angle;
	float radius;
	float maxRange;
	bool opponentDetected;
	Point2D *currentPosition;
	bool inRadius(Vec2 point);
	bool inRange(Vec2 point);
	void reconnect();
	bool isPointNull(Vec2 v);
	int detectedAngle;
};