#pragma once

class Vec2
{
public:
	float A;
	float B;
	Vec2(float a, float b);
};

float degToRad(float degrees);
float mmToSteps(float distance);
float StepsTomm(float steps);

float normalizeAngle(float angle);
