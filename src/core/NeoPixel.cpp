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
		}
		FastLED.show();
	}
	if (color == 2)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = CRGB::Blue;
		}
		FastLED.show();
	}
	if (color == 3)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = CRGB::White;
		}
		FastLED.show();
	}
}

void NeoPixel::fire2012()
{
	static uint8_t heat[NUM_LEDS];
	for (int i = 0; i < NUM_LEDS; i++)
	{
		heat[i] = qsub8(heat[i], random8(0, ((55 * 10) / NUM_LEDS) + 2));
	}

	for (int k = NUM_LEDS - 1; k >= 2; k--)
	{
		heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
	}
	if (random8() < 120)
	{
		int y = random8(7);
		heat[y] = qadd8(heat[y], random8(160, 255));
	}
	for (int j = 0; j < NUM_LEDS; j++)
	{
		CRGB color = HeatColor(heat[j]);
		leds[j] = color;
	}
	FastLED.show();
}

void NeoPixel::pride()
{
	static uint16_t sPseudotime = 0;
	static uint16_t sLastMillis = 0;
	static uint16_t sHue16 = 0;

	uint8_t sat8 = beatsin88(87, 220, 250);
	uint8_t brightdepth = beatsin88(341, 96, 224);
	uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
	uint8_t msmultiplier = beatsin88(147, 23, 60);

	uint16_t hue16 = sHue16; // gHue * 256;
	uint16_t hueinc16 = beatsin88(113, 1, 3000);

	uint16_t ms = millis();
	uint16_t deltams = ms - sLastMillis;
	sLastMillis = ms;
	sPseudotime += deltams * msmultiplier;
	sHue16 += deltams * beatsin88(400, 5, 9);
	uint16_t brightnesstheta16 = sPseudotime;

	for (uint16_t i = 0; i < NUM_LEDS; i++)
	{
		hue16 += hueinc16;
		uint8_t hue8 = hue16 / 256;

		brightnesstheta16 += brightnessthetainc16;
		uint16_t b16 = sin16(brightnesstheta16) + 32768;

		uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
		uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
		bri8 += (255 - brightdepth);

		CRGB newcolor = CHSV(hue8, sat8, bri8);

		uint16_t pixelnumber = i;
		pixelnumber = (NUM_LEDS - 1) - pixelnumber;

		nblend(leds[pixelnumber], newcolor, 64);
	}
	FastLED.show();
}