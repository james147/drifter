#include <Motor.h>
#include <Button.h>
#include <LED.h>

Button switch1(4, PULLUP);
Button switch2(8, PULLUP);
LED led1(9);  // PWM pin
LED led2(13); // Non PWM pin
Motor left_motor;
Motor right_motor;

bool running = false;
int speed = -1;

void setup()
{
    Serial.begin(9600);
    left_motor.attach(10, 11, 12);
    right_motor.attach(5, 6, 7);
}

void loop()
{
    // Stop if the user has pressed the second switch
    if (switch2.uniquePress()) {
        running = false;
        speed = -1;
        left_motor.stop();
        right_motor.stop();
        return;
    }
    
    // Incroment speed if the first switch is pressed
    if (switch1.uniquePress()) {
        speed++;
        if (speed > 10) {
            speed = 0;
        }
        left_motor.forward(speed);
        right_motor.forward(speed);
    }
    
}
