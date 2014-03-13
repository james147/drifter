#include <Motor.h>

void Motor::_update() {
    switch (_state) {
        case FORWARD:
            digitalWrite(_forward_pin, HIGH);
            digitalWrite(_reverse_pin, LOW);
            analogWrite(_enable_pin, map(_speed, 1, 10, MIN_POWER, MAX_POWER));
            break;
        case REVERSE:
            digitalWrite(_forward_pin, LOW);
            digitalWrite(_reverse_pin, HIGH);
            analogWrite(_enable_pin, map(_speed, 1, 10, MIN_POWER, MAX_POWER));
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

Motor(int enable_pin, int forward_pin, int reverse_pin) {
    _enable_pin = enable_pin;
    _forward_pin = forward_pin;
    _reverse_pin = reverse_pin;
}

void Motor::begin() {
    pinMode(_enable_pin, OUTPUT);
    pinMode(_forward_pin, OUTPUT);
    pinMode(_reverse_pin, OUTPUT);
    digitalWrite(_enable_pin, LOW);
    digitalWrite(_forward_pin, LOW);
    digitalWrite(_reverse_pin, LOW);
}

void Motor::setSpeed(byte speed) {
    _speed = speed;
   _update(); 
}

void Motor::forward(byte speed) {
    _speed = speed;
    _state = FORWARD;
    _update();
}

void Motor::forward() {
    _state = FORWARD;
    _update();
}

void Motor::reverse(byte speed) {
    _speed = speed;
    _state = REVERSE;
    _update();
}

void Motor::reverse() {
    _state = REVERSE;
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

