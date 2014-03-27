#include <Arduino.h>
#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
    public:
        /** The state the motor can be in. */
        enum State {
            MOVING,  /** Causes the motor to spin. */
            STOPPED, /** Causes the to activly break, if the motor supports this. */
            OFF      /** Turns the motor off. */
        };

        /** Creates a motor object attached to the given pins.
         *
         *  \param enable_pin the h-bridge enable pin for the motor.
         *  \param forward_pin the h-bridge pin to make the motor spin forward.
         *  \param reverse_pin the h-bridge pin to make the motor spin in reverse.
         */
        Motor(int enable_pin, int forward_pin, int reverse_pin);

        /** Sets the speed of the motor.
         *
         *  \param speed the speed of the motor as a value from -10 to 10
         */
        void setSpeed(int8_t speed);

        /** Sets the maximum power of the motor
         *
         *  \param power the power level to set the maximum power to
         * */
        void setMaxPower(uint8_t power);

        /** Sets the minimum power of the motor
         *
         *  \param power the power level to set the minimum power to
         * */
        void setMinPower(uint8_t power);

        State state() { return _state; }
        int8_t speed() { return _speed; }
        uint8_t maxPower() { return _max_power; }
        uint8_t minPower() { return _min_power; }

        /** Causes the motors to break.
         *
         *  If the motors support breaking this causes them to activly break
         *  and resist movment, slowing them faster then off() otherwise it is
         *  equlivent to off().
         */
        void stop();

        /** Turns the motors off
         *
         *  Turns off the motors, but does not cause them to break or suddenly
         *  stop. Depending on the motor it might not stop stright away but
         *  will slowly come to a stop.
         */
        void off();

    private:
        int8_t _speed; /** The speed of the motor, holds a value from -10 to 10. */
        uint8_t _max_power; /** The maximum power needed to make the motor spin. */
        uint8_t _min_power; /** The minimum power needed to make the motor spin. */
        State _state; /** The state the motor is currently in. */
        uint8_t _enable_pin;
        uint8_t _forward_pin;
        uint8_t _reverse_pin;

        /** Updates the motors state to match the varibles above. */
        void _update();
};

#endif // MOTOR_H
