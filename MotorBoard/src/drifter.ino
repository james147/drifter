#include <Arduino.h>
#include <Button.h>
#include <LED.h>
#include <EEPROM.h>
#include "Robot.h"
#include "Motor.h"
#include "Commands.h"

Robot robot;
SerialCommands commands;
int left_ir = 0;
int center_ir = 1;
int right_ir = 2;
Button button(11, PULLUP);

void test() {
  Serial.println("WORKING");
}

void setup() {
    robot.init();
    pinMode(left_ir, INPUT);
    pinMode(center_ir, INPUT);
    pinMode(right_ir, INPUT);
    Serial.begin(9200);
    commands.begin(&Serial);
}

bool running = false;

void loop() {
    if (button.uniquePress()) {
        Serial.println(button.isPressed());
        running = !running;
    }
    delay(10);
    if (running) {
        Serial.println("START");
        bool left_reading = triggered(left_ir);
        bool center_reading = triggered(center_ir);
        bool right_reading = triggered(right_ir);

        if (left_reading && center_reading && right_reading) {
            Serial.println("Stop");
            robot.stop();
        } else if (left_reading) {
            Serial.println("Left");
            robot.setSpeed(1, 0);
        } else if (right_reading) {
            Serial.println("Right");
            robot.setSpeed(0, 1);
        } else {
            Serial.println("Forward");
            robot.setSpeed(1, 1);
        }
    } else {
        robot.stop();
    }
    return;
    commands.processSerial();
}

bool triggered(int pin) {
    int reading = analogRead(pin);
    Serial.print(reading);
    Serial.print("  ");
    Serial.println(reading > 700);
    return reading > 700;
}
