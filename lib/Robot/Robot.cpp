#include <Robot.h>

Robot::Robot() : 
        led(13), 
        button(10, PULLUP),
        _left_motor(6,5,4),
        _right_motor(9, 8,7),
        _running(false),
        _speed(1),
        _state(OFF) {
    loadSettings();
}

void Robot::init() {
}

void Robot::loadSettings() {
    byte left_min = EEPROM.read(LEFT_MIN_POWER_ADDRESS);
    byte right_min = EEPROM.read(RIGHT_MIN_POWER_ADDRESS);

    if (right_min > 100 || left_min > 100) {
        left_min = 50;
        right_min = 50;
    } else {
        _left_motor.setMinPower(left_min);
        _right_motor.setMinPower(right_min);
    }
}

void Robot::saveSettings() {
}

void Robot::forward(int speed) {
    _speed = speed;
    _state = FORWARD;
    _left_motor.forward(speed);
    _right_motor.forward(speed);
}

void Robot::reverse(int speed) {
    _speed = speed;
    _state = REVERSE;
    _left_motor.reverse(speed);
    _right_motor.reverse(speed);
}

void Robot::stop() {
    _left_motor.stop();
    _right_motor.stop();
    _state = STOPPED;
}

void Robot::off() {
    _left_motor.off();
    _right_motor.off();
    _state = OFF;
}

bool Robot::isRunning() {
    return _state != STOPPED && _state != OFF;
}
