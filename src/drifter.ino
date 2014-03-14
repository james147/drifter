#include <Arduino.h>
#include <Motor.h>
#include <Button.h>
#include <LED.h>
#include <Potentiometer.h>
#include <EEPROM.h>

Potentiometer pot(0);
Button switch1(4, PULLUP);
Button switch2(8, PULLUP);
LED led1(9);  // PWM pin
LED led2(13); // Non PWM pin
Motor left_motor;
Motor right_motor;
static const int LEFT_MIN_POWER_ADDRESS = 0;
static const int RIGHT_MIN_POWER_ADDRESS = 1;

bool running = false;
int speed = 0;

void setup()
{
    Serial.begin(9600);
    left_motor.attach(10, 11, 12);
    right_motor.attach(5, 6, 7);
    Serial.println("Press switch1 to start calibration");
    led1.fadeIn(250);
    led1.fadeOut(250);
    if (switch1.isPressed()) {
        calibrateMotors();
    } else {
        Serial.println("Loading EEPROM values");
        byte left_min = EEPROM.read(LEFT_MIN_POWER_ADDRESS);
        byte right_min = EEPROM.read(RIGHT_MIN_POWER_ADDRESS);
        Serial.print("Left motor min power: ");
        Serial.println(left_min);
        Serial.print("Right motor min power: ");
        Serial.println(right_min);

        if (right_min > 100 || left_min > 100) {
            Serial.println("Bad values detected in EEPROM, running calibration");
            calibrateMotors();
        } else {
            left_motor.setMinPower(left_min);
            right_motor.setMinPower(right_min);
        }
    }
    Serial.println("Started");
}

void loop()
{
    // Stop if the user has pressed the second switch
    if (switch2.uniquePress()) {
        running = false;
        speed = 0;
        left_motor.stop();
        right_motor.stop();
        return;
    }
    
    // Incroment speed if the first switch is pressed
    if (switch1.uniquePress()) {
        speed++;
        if (speed > 10) {
            speed = 1;
        }
        left_motor.forward(speed);
        right_motor.forward(speed);
    }
    
}

void calibrateMotors() {
    byte min_power;
    int offset_power;

    Serial.println("Entering configure mode");
    led1.on();
    led2.on();
    delay(500);
    led1.off();
    led2.off();
    delay(500);
    led1.on();
    led2.on();

    Serial.println("Calibrating Motor Min Power");
    Serial.println("Turn pot to the minimum position then up until the rover starts moving, then press switch1 to continue");

    while (pot.getValue()) {
        delay(100);
    }

    left_motor.forward(1);
    right_motor.forward(1);
    
    // Find base min power
    while (true) {
        min_power = map(pot.getValue(), 0, 1023, 0, 255);
        Serial.println(min_power);
        left_motor.setMinPower(min_power);
        right_motor.setMinPower(min_power);

        if (switch1.uniquePress()) {
            left_motor.stop();
            right_motor.stop();
            break;
        }

        delay(100);
    }

    Serial.println("Balancing the motors");
    Serial.println("Adjust the pot to the center position, the rover will then start to move forward at the minimum speed, adjust the pot left or right to until the rover drives stright, then press switch1 to continue");

    while (abs(map(pot.getValue(), 0, 1023, -50, 50)) > 2) {
        if (offset_power > 0) {
            led1.on();
            led2.off();
        } else if (offset_power < 0 ) {
            led1.off();
            led2.on();
        }
        led1.on();
        led2.on();
        delay(100);
    }
    delay(1000);

    left_motor.forward(1);
    right_motor.forward(1);
    

    // Find the offset of the two motors
    while (true) {
        offset_power = map(pot.getValue(), 0, 1023, -50, 50);
        Serial.println(offset_power);

        if (offset_power > 0) {
            Serial.print("Adjusting left");
            Serial.println(min_power + offset_power);
            left_motor.setMinPower(min_power + offset_power);
        } else if (offset_power < 0 ) {
            Serial.print("Adjusting right ");
            Serial.println(min_power + abs(offset_power));
            right_motor.setMinPower(min_power + abs(offset_power));
        }

        if (switch1.uniquePress()) {
            left_motor.stop();
            right_motor.stop();
            break;
        }

        delay(100);
    }

    Serial.print("Final values, left min power: ");
    Serial.print(left_motor.minPower());
    Serial.print(" right min power: ");
    Serial.print(right_motor.minPower());
    EEPROM.write(LEFT_MIN_POWER_ADDRESS, left_motor.minPower());
    EEPROM.write(RIGHT_MIN_POWER_ADDRESS, right_motor.minPower());
}
