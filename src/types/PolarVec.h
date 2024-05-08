#pragma once
#include <types/Steps.h>
#include <math.h>
#include <utils/utils.h>
#include <Arduino.h>

class PolarVec
{
private:
	float angle;
	float distance;

public:
	// 1.angle 2.distance
	PolarVec(float angle, float distance);

	float getAngle();
	float getDistance();
	Steps ToSteps();
	Vec2 toVec2();
};