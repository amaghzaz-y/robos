#include <Arduino.h>
// #include <types/PolarVec.h>
// #include <core/Lidar.h>
// #include <core/Strategy.h>
// #include <lib/ticker/Ticker.h>

// Strategy strategy;
// Lidar lidar;

// bool lidarStatus = false;
// Point2D currentPoint = Point2D(0, 0);

// Ticker ticker([]
//               { strategy.stop(); },
//               95500, 0, MILLIS);

// void LidarTask(void *pvParameters)
// {
//     int count = 0;
//     for (;;)
//     {
//         currentPoint = strategy.getCurrentPoint();
//         if (lidar.Task(&currentPoint))
//             count++;
//         if (count > 15)
//         {
//             lidarStatus = true;
//             count = 0;
//         }
//         else
//         {
//             lidarStatus = false;
//         }
//         ticker.update();
//     }
// }

// bool value = false;

void setup()
{
    // delay(2000);
    Serial.begin(9600);
    Serial.println("setup start");
    // Serial.println("setup start");
    // value = strategy.actuators.servoDriver.begin();
    // strategy.actuators.servoDriver.setOscillatorFrequency(50000000);
    // strategy.actuators.servoDriver.setPWMFreq(1600);
    // for (int i = 0; i < 16; i++)
    // {
    //     strategy.actuators.servoDriver.setPWM(i, 0, 0);
    // }
    // strategy.actuators.servoDriver.sleep();

    // strategy.actuators.servoDriver.setPWM(0, 0, 4096);
    // strategy.actuators.servoDriver.setPWM(1, 4096, 0);
    // Serial.begin(9600);
    // Serial.println("setup start");
    // lidar.setup();
    // lidar.setMaxRange(450); // 300
    // lidar.setRadius(360);
    // lidar.setAngle(180);
    // strategy.setup();
    // strategy.display.Show("SCORE", "35", "", "");
    // Serial.println("setup done");
    // xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
    // strategy.actuators.servoDriver.setOutputMode(1);
}

void loop()
{
    Serial.print("value : ");
    // Serial.println(value);
    delay(1000);
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