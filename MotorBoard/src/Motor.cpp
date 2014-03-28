#include "Motor.h"

void Motor::_update() {
    switch (_state) {
        case MOVING:
            // Pick direction
            if (_speed >= 0) {
                digitalWrite(_forward_pin, HIGH);
                digitalWrite(_reverse_pin, LOW);
            } else {
                digitalWrite(_forward_pin, LOW);
                digitalWrite(_reverse_pin, HIGH);
            }
            Serial.print("Speed '");
            Serial.print(_forward_pin);
            Serial.print("' '");
            Serial.print(digitalRead(_forward_pin));
            Serial.print("' '");
            Serial.print(_reverse_pin);
            Serial.print("' '");
            Serial.print(digitalRead(_reverse_pin));
            Serial.print("' '");
            Serial.print(_enable_pin);
            Serial.print("' '");
            Serial.print(digitalRead(_enable_pin));
            Serial.print("': ");
            Serial.println(_speed);

            // Make the motors move
            if (_speed == 0) {
                digitalWrite(_enable_pin, LOW);
            } else {
                analogWrite(_enable_pin, map(_speed, 1, 10, _min_power, _max_power));
            }
            break;
        case STOPPED:
            digitalWrite(_forward_pin, LOW);
            digitalWrite(_reverse_pin, LOW);
            digitalWrite(_enable_pin, HIGH);
            break;
        case OFF:
            digitalWrite(_forward_pin, LOW);
            digitalWrite(_reverse_pin, LOW);
            digitalWrite(_enable_pin, LOW);
            break;
    }
}

Motor::Motor(int enable_pin, int forward_pin, int reverse_pin) :
        _speed(0),
        _state(OFF),
        _enable_pin(enable_pin),
        _forward_pin(forward_pin),
        _reverse_pin(reverse_pin),
        _max_power(255),
        _min_power(50) {
    pinMode(_enable_pin, OUTPUT);
    pinMode(_forward_pin, OUTPUT);
    pinMode(_reverse_pin, OUTPUT);
    _update();
}

void Motor::setSpeed(int8_t speed) {
    _state = MOVING;
    _speed = speed;
    _update(); 
}

void Motor::setMaxPower(uint8_t power) {
    _max_power = power;
    _update();
}

void Motor::setMinPower(uint8_t power) {
    _min_power = power;
    _update();
}

void Motor::stop() {
    _state = STOPPED;
    _update();
}

void Motor::off() {
    _state = OFF;
    _update();
}

