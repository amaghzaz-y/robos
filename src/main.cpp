#include <Arduino.h>
#include <types/PolarVec.h>
#include <core/Lidar.h>
#include <core/Strategy.h>
#include <lib/ticker/Ticker.h>

Strategy strategy;
Lidar lidar;

bool lidarStatus = false;

Point2D currentPoint = Point2D(0, 0);

Ticker ticker([]
              { strategy.stop(); },
              95500, 0, MILLIS);

void LidarTask(void *pvParameters)
{
    int count = 0;
    for (;;)
    {
        currentPoint = strategy.getCurrentPoint();
        if (lidar.Task(&currentPoint))
            count++;
        if (count > 15)
        {
            lidarStatus = true;
            // Serial.println("DETECTED");
            count = 0;
        }
        else
        {
            lidarStatus = false;
        }
        ticker.update();
    }
}

int value = 0;

void setup()
{
    // delay(2000);
    Serial.begin(9600);
    Serial.println("setup start");
    lidar.setup();
    lidar.setMaxRange(350); // 300
    lidar.setRadius(360);
    lidar.setAngle(180);
    strategy.setup();
    strategy.display.Show(" KISS", "  MY", "   ASS", "    XOXO <3");
    Serial.println("setup done");
    xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
}

void loop()
{
    strategy.Initiation();
    strategy.Ready();
    // ticker.start();
    // strategy.Homologuation(&lidarStatus);
    strategy.start(&lidarStatus);
}