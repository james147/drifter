#include <Arduino.h>
#include <Motor.h>
#include <Button.h>
#include <LED.h>
#include <EEPROM.h>
#include <Robot.h>
//#include <Commands.h>

Robot robot;

void setup() {
    robot.init();
    //Commands.begin(9600);
    Serial.println("HELLO");
}

void loop() {
    delay(50);
    if (robot.button.uniquePress()) {
        if (robot.isRunning()) {
            robot.stop();
        } else {
            robot.forward(5);
        }
    }
}

