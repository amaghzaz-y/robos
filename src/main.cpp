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
            count = 0;
        }
        else
        {
            lidarStatus = false;
        }
        ticker.update();
    }
}

void setup()
{
    Serial.begin(9600);
    Serial.println("setup start");
    lidar.setup();
    lidar.setMaxRange(450); // 300
    lidar.setRadius(360);
    lidar.setAngle(180);
    strategy.setup();
    strategy.display.Show("SCORE", "35", "", "");
    Serial.println("setup done");
    // xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
    // strategy.actuators.servoDriver.setOutputMode(1);
}

void loop()
{
    // strategy.Initiation();
    // strategy.Ready();
    // ticker.start();
    // strategy.actuators.servoDriver.writeMicroseconds(0, 2500);
    // delay(2000);
    // strategy.actuators.servoDriver.setPin(0, 1500);
    // delay(2000);
    // strategy.display.Show("SCORE", "35", "", "");
    // strategy.start(&lidarStatus);
    // strategy.Initiation();
    // strategy.display.Show("SCORE", "35", "", "");
    // while (1)
    // {
    // strategy.neopixel.pride();
    //     delay(2000);
    //     strategy.display.Show("SCORE", "35", "LIDAR DETECTION", lidarStatus ? "ON" : "OFF");
    // }
}