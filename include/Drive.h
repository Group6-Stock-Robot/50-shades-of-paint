#ifndef DRIVE_H
#define DRIVE_H

#include <Motor.h>

class Drive {

    const uint8_t BASE_SPEED = 30;
    Motor * leftMotor;
    Motor * rightMotor;

public:
    Drive(Motor * rightMotor, Motor * leftMotor);
    void init();
    void drive();
    void drive(int speed);
    void drive(int lSpeed, int rSpeed);
    void stop();
    void rotate(uint8_t turnDirection);
    void rotate(int speed, uint8_t turnDirection);
    void turnAround(uint8_t turnDirection);
    void turnAround(int speed, uint8_t turnDirection);
};

#endif // DRIVE_H
