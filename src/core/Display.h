#pragma once
#include <LiquidCrystal_I2C.h>
#include <utils/PINS.h>

class Display
{
private:
	LiquidCrystal_I2C lcd;

public:
	Display();
	void setup();
	void Show(String row0, String row1, String row2, String row3);
	void Test();
};