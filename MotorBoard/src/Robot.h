#include <Arduino.h>
#include "Motor.h"
#include <Button.h>
#include <LED.h>
#include <EEPROM.h>

#ifndef ROBOT_H
#define ROBOT_H

class Robot
{
    private:
        static const int LEFT_MIN_POWER_ADDRESS = 0;
        static const int RIGHT_MIN_POWER_ADDRESS = 1;

    public:
        enum State {
            FORWARD, 
            REVERSE,
            STOPPED,
            OFF,
            ROTATING_LEFT,
            ROTATING_RIGHT
        };

        Robot();
        void init();
        void loadSettings();
        void saveSettings();
        void forward(int speed);
        void reverse(int speed);
        void stop();
        void off();
        
        bool isRunning();

        Button button;
        LED led;

    private:
        Motor _left_motor;
        Motor _right_motor;

        bool _running;
        int _speed;
        State _state;
};

#endif // ROBOT_H
