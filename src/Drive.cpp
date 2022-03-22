#include "Drive.h"
#include <Definitions.h>

Drive::Drive(Motor * rightMotor, Motor * leftMotor)
    : leftMotor(leftMotor),
    rightMotor(rightMotor) {

}

void Drive::init() {
    leftMotor->init();
    rightMotor->init();
}

void Drive::drive() {
    drive(BASE_SPEED);
}

void Drive::drive(int speed) {
    drive(speed, speed);
}
void Drive::drive(int lSpeed, int rSpeed) {
    if (lSpeed > 0)
        leftMotor->forward(lSpeed);
    else if (lSpeed == 0)
        leftMotor->stop();
    else
        leftMotor->reverse(-lSpeed);

    if (rSpeed > 0)
        rightMotor->forward(rSpeed);
    else if (rSpeed == 0)
        rightMotor->stop();
    else
        rightMotor->reverse(-rSpeed);
}


void Drive::stop() {
    leftMotor->stop();
    rightMotor->stop();
}

void Drive::rotate(uint8_t turnDirection) {
    rotate(BASE_SPEED, turnDirection);
}
void Drive::rotate(int speed, uint8_t turnDirection) {
    if (turnDirection == RIGHT) {
        leftMotor->forward(speed);
        rightMotor->stop();
    }
    if (turnDirection == LEFT) {
        rightMotor->forward(speed);
        leftMotor->stop();
    }
}

void Drive::turnAround(uint8_t turnDirection) {
    turnAround(BASE_SPEED, turnDirection);
}
void Drive::turnAround(int speed, uint8_t turnDirection) {
    if (turnDirection == LEFT) {
        rightMotor->forward(speed);
        leftMotor->reverse(speed);
    }
    if (turnDirection == RIGHT) {
        leftMotor->forward(speed);
        rightMotor->reverse(speed);
    }
}
