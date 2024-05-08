#include "NeoPixel.h"
#include "Arduino.h"
#include <utils/PINS.h>
void NeoPixel::setup()
{
	Serial.println("NEOPIXEL :: SETUP");
	delay(500);
	FastLED.addLeds<CHIPSET, PIN_NEOPIXEL, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(BRIGHTNESS);
	FastLED.clear(true);
	for (int i = 0; i < NUM_LEDS; i++)
	{
		// For each pixel...
		leds[i] = CRGB::Red;
		FastLED.show();
		delay(1);
	}
	Serial.println("NEOPIXEL :: SETUP DONE");
}

// 0 for red, 1 for yellow, 2 for blue, 3 for while
void NeoPixel::changeColor(int color)
{
	if (color == 0)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = CRGB::Red;
		}
		FastLED.show();
	}
	if (color == 1)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = CRGB::Yellow;
			FastLED.show();
		}
	}
	if (color == 2)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = CRGB::Blue;
			FastLED.show();
		}
	}
	if (color == 3)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = CRGB::White;
			FastLED.show();
		}
	}
}