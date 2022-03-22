#include "Motor.h"
/**
 * @brief Construct a new Motor:: Motor object
 *
 * @param in1 For left motor it's the odd pin INx, for the right motor even pin INx
 * @param in2 For left motor it's the even pin INx, for the right motor odd pin INx
 * @param _decay
 */
Motor::Motor(int in1, int in2, int _decay)
    : oddPin(in1),
    evenPin(in2),
    decay(_decay) {
}
/**
 * @brief
 * Call this in the setup to initiate the Motor object.
 * @return * void
 */
void Motor::init() {
    pinMode(evenPin, OUTPUT);
    pinMode(oddPin, OUTPUT);
}
/**
 * @brief
 *  Turn the motor forward,
 * @param _speed int from 0 to 100
 * @return * void
 */
void Motor::forward(int _speed) {
    forward(_speed, decay);
}

void Motor::forward(int _speed, uint8_t _decay) {
    if (_decay == SLOW_DECAY) {
        forwardSlowDecay(_speed);
    }
    if (_decay == FAST_DECAY) {
        forwardFastDecay(_speed);
    }
}

void Motor::reverse(int _speed) {
    reverse(_speed, decay);
}

void Motor::reverse(int _speed, uint8_t _decay) {
    if (decay == SLOW_DECAY) {
        reverseSlowDecay(_speed);
    }
    if (decay == FAST_DECAY) {
        reverseFastDecay(_speed);
    }
}
/**
 * @brief
 * Stop the motor
 * @return * void
 */
void Motor::stop() {
    stop(decay);
}
void Motor::stop(uint8_t _decay) {
    digitalWrite(oddPin, _decay);
    digitalWrite(evenPin, _decay);
}
/**
 * @brief
 * Internal function for the Motor class to turn the 0-100 speed to pwm
 * @return int pwm value corresponding to the speed provided
 */
int Motor::speedToPWM(int _speed) {
    int speed = constrain(_speed, 0, 100);
    return map(speed, 0, 100, 100, 255);
}
/*
Pin control of the H-Bridge from datasheet:
###############################################
#   xIN1  |  xIN2  |  FUNCTION                #
#---------------------------------------------#
#   PWM   |  0     |  Forward PWM, fast decay #
#   1     |  PWM   |  Forward PWM, slow decay #
#   0     |  PWM   |  Reverse PWM, fast decay #
#   PWM   |  1     |  Reverse PWM, slow decay #
###############################################

 */
/**
 * @brief
 * Internal function for the Motor class used internally do the pin magic to get the robot moving.
 * Uses fast decay mode of the H-Bridge
 * @param speed speed value 0 - 100
 * @return * void
 */
void Motor::forwardSlowDecay(int speed) {
    int pwm = speedToPWM(speed);
    digitalWrite(evenPin, HIGH);
    analogWrite(oddPin, pwm);
}

void Motor::forwardFastDecay(int speed) {
    int pwm = speedToPWM(speed);
    analogWrite(evenPin, pwm);
    digitalWrite(oddPin, LOW);
}

void Motor::reverseSlowDecay(int speed) {
    int pwm = speedToPWM(speed);
    analogWrite(evenPin, pwm);
    digitalWrite(oddPin, HIGH);
}

void Motor::reverseFastDecay(int speed) {
    int pwm = speedToPWM(speed);
    digitalWrite(evenPin, LOW);
    analogWrite(oddPin, pwm);
}
