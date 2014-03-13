#include <Arduino.h>
#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
    private:
        /** The state the motor can be in. */
        enum State {
            FORWARD, /** Causes the motor to spin in a forward direction. */
            REVERSE, /** Causes the motor to spin in the opposite direction to FORWARD. */
            STOPPED, /** Causes the to activly break, if the motor supports this. */
            OFF,     /** Turns the motor off. */
            DETACHED /** The motor has not yet been attached. */
        };
        byte _speed; /** The speed of the motor, holds a value from 1 to 10. */
        static const byte MAX_POWER = 255; /** The maximum power needed to make the motor spin. */
        static const byte MIN_POWER = 100; /** The minimum power needed to make the motor spin. */
        State _state; /** The state the motor is currently in. */
        int _enable_pin;
        int _forward_pin;
        int _reverse_pin;

        /** Updates the motors state to match the varibles above. */
        void _update();

    public:

        /** Creates a motor object attached to the given pins.
         *
         *  \param enable_pin the h-bridge enable pin for the motor.
         *  \param forward_pin the h-bridge pin to make the motor spin forward.
         *  \param reverse_pin the h-bridge pin to make the motor spin in reverse.
         */
        Motor();

        /** Attaches to the h-bridge and sets up the pins. 
         *
         * This function must be called before calling any other function and
         * is generally done in the setup() function.
         */
        void attach(int enable_pin, int forward_pin, int reverse_pin);

        /** Detaches form the h-bridge, 
         *
         * This function must be called before calling any other function and
         * is generally done in the setup() function.
         */
        void detach();

        /** Sets the speed of the motor.
         *
         *  \param speed the speed of the motor as a value from 1 to 10
         */
        void setSpeed(byte speed);

        /** Sets the speed and direction of the motor to forward.
         *
         *  \param speed the speed of the motor as a value form 1 to 10
         */
        void forward(byte speed);

        /** Sets the direction of the motors to forward at the current speed.
        */
        void forward();

        /** Sets the speed and direction of the motor to reverse.
         *
         *  \param speed the speed of the motor as a value form 1 to 10
         */
        void reverse(byte speed);

        /** Sets the direction of the motors to reverse at the current speed.
        */
        void reverse();

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
};

#endif // MOTOR_H
