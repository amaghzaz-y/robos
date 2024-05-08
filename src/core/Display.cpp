#include <core/Display.h>
#include <Arduino.h>

Display::Display() : lcd(0x3F, 20, 4)
{
}
void Display::setup()
{
	Serial.println("Display :: setup");
	// (0x3F, 16, 2)
	lcd.init(PIN_SDA, PIN_SCL); // initialize the lcd to use user defined I2C pins
	lcd.backlight();
	Serial.println("Display :: setup done");
}

void Display::Show(String row0, String row1, String row2, String row3)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(row0);
	lcd.setCursor(0, 1);
	lcd.print(row1);
	lcd.setCursor(0, 2);
	lcd.print(row2);
	lcd.setCursor(0, 3);
	lcd.print(row3);
	lcd.display();
}

void Display::Test()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.println("hello MF");
	lcd.display();
}