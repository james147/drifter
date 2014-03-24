#include <Arduino.h>
#include <Button.h>
#include <LED.h>
#include <EEPROM.h>
#include "Robot.h"
#include "Motor.h"
#include "Commands.h"

Robot robot;
SerialCommands commands;

void processCommand() {
  Command command = commands.next();
  switch(command.id) {
    case 'm':
      // setSpeed/move
      byte left_speed;
      byte right_speed;
      
      if (command.length == 1) {
        left_speed = command.args[0];
        right_speed = command.args[0];
      } else if (command.length == 2) {
        left_speed = command.args[0];
        right_speed = command.args[1];
      } else {
        Serial.println("Error, invalid number of arguments");
        break;
      }
      
      break;
    case 'b':
      // stop/break
      break;
    case 'o':
      // off
      break;
    default:
      Serial.println("Error, command not found");
  }
}

void setup() {
    robot.init();
    Serial.begin(9200);
    commands.begin(&Serial);
}

void loop() {
    delay(5);
    if (Serial.available()) {
      Serial.print("Got: ");
      Serial.println((char)Serial.read());
    }
    return;
    Command command = commands.next();
    if (command.id != 0) {
      Serial.print(command.id);
      Serial.print(" ");
      Serial.print(command.length);
      for (int i = 0; i < command.length; i++) {
        Serial.print(" ");
        Serial.print(command.args[i]);
      }
      Serial.println();
    }
}

