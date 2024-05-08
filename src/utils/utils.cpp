#include <utils/utils.h>
#include <math.h>
Vec2::Vec2(float a, float b)
{
	A = a;
	B = b;
}

float mmToSteps(float mm)
{
	return (mm * 4000) / 188.496;
}

float StepsTomm(float steps)
{
	return 188.496 * steps / 4000;
}

float degToRad(float degrees)
{
	return degrees * 0.017453292519943295769236907684886;
}

float normalizeAngle(float angle)
{
	angle = fmod(angle + 180, 360);
	if (angle < 0)
		angle += 360;
	return angle - 180;
}
