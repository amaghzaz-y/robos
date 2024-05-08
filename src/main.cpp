#include <Arduino.h>
#include <types/PolarVec.h>
#include <core/Lidar.h>
#include <core/Strategy.h>
#include <lib/ticker/Ticker.h>

Strategy strategy;
Lidar lidar;

bool lidarStatus = false;
Point2D currentPoint = Point2D(0, 0);

void FullStop()
{
    strategy.stop();
}
Ticker ticker(FullStop,
              95500, 0, MILLIS);

void LidarTask(void *pvParameters)
{
    for (;;)
    {
        currentPoint = strategy.getCurrentPoint();
        lidarStatus = lidar.Task(&currentPoint);
        ticker.update();
    }
}

void setup()
{
    Serial.begin(9600);
    lidar.setup();
    lidar.setMaxRange(320); // 300
    lidar.setRadius(360);
    lidar.setAngle(180);
    strategy.setup();
    xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
}

void loop()
{
    // strategy.testINPUT();
    strategy.Initiation();
    strategy.Ready();
    ticker.start();
    strategy.stratA_BLUE(&lidarStatus);
    strategy.display.Show("SCORE", "45", "", "");
    strategy.actuators.funnyAction();
    while (1)
        ;
    ;
}