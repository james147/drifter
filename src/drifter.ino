#include <Arduino.h>
#include <Motor.h>
#include <Button.h>
#include <LED.h>
#include <EEPROM.h>

Button button(A0, PULLUP);
LED led(13);
Motor left_motor;
Motor right_motor;
static const int LEFT_MIN_POWER_ADDRESS = 0;
static const int RIGHT_MIN_POWER_ADDRESS = 1;

bool running = false;
int speed = 5;

void setup()
{
    Serial.begin(9600);
    left_motor.attach(9, 8, 7);
    right_motor.attach(6, 5, 4);
    Serial.println("Loading EEPROM values");
    byte left_min = EEPROM.read(LEFT_MIN_POWER_ADDRESS);
    byte right_min = EEPROM.read(RIGHT_MIN_POWER_ADDRESS);

    if (right_min > 100 || left_min > 100) {
        Serial.println("Values uninitlised, initlising");
        left_min = 50;
        right_min = 50;
    } else {
        left_motor.setMinPower(left_min);
        right_motor.setMinPower(right_min);
    }
    Serial.print("Left motor min power: ");
    Serial.println(left_min);
    Serial.print("Right motor min power: ");
    Serial.println(right_min);
    Serial.println("Started");
}

void loop()
{
    if (button.uniquePress()) {
        if (running) {
            left_motor.stop();
            right_motor.stop();
            running = false;
        } else {
            left_motor.forward(speed);
            right_motor.forward(speed);
            running = true;
        }
    }
}

