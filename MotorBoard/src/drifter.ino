#include <Arduino.h>
#include <Button.h>
#include <LED.h>
#include <EEPROM.h>
#include "Robot.h"
#include "Motor.h"
#include "Commands.h"

Robot robot;
SerialCommands commands;

void test() {
  Serial.println("WORKING");
}

void setup() {
    robot.init();
    Serial.begin(9200);
    commands.begin(&Serial);
}

void loop() {
    delay(5);
    commands.processSerial();
    return;
}

