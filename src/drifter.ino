#include <Arduino.h>
#include <Motor.h>
#include <Button.h>
#include <LED.h>
#include <EEPROM.h>
#include <Robot.h>

Robot robot;

void setup() {
    Serial.begin(9600);
    robot.init();
}

void loop() {
    if (robot.button.uniquePress()) {
        if (robot.isRunning()) {
            robot.stop();
        } else {
            robot.forward(5);
        }
    }
}

String command = "";

void serialEvent() {
    
}
