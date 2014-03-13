#include <Motor.h>
#include <Button.h>

Button switch1;
Button switch2;
Motor left_motor;
Motor right_motor;

void setup()
{
    switch1.attach(4);
    switch2.attach(8);
    left_motor.attach(10, 11, 12);
    right_motor.attach(5, 6, 7);
}

void loop()
{
    int speed = 1;
    left_motor.forward(speed);
    right_motor.forward(speed);
}
