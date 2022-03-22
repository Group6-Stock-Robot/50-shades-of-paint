#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define SLOW_DECAY 1
#define FAST_DECAY 0

class Motor {
    uint8_t oddPin;
    uint8_t evenPin;
    uint8_t decay;

public:
    Motor(int in1, int in2, int _decay = FAST_DECAY);
    void init();

    void forward(int _speed);
    void forward(int _speed, uint8_t _decay);

    void reverse(int _speed);
    void reverse(int _speed, uint8_t _decay);

    void stop();
    void stop(uint8_t _decay);

private:
    int speedToPWM(int _speed);

    void forwardSlowDecay(int speed);
    void forwardFastDecay(int speed);

    void reverseSlowDecay(int speed);
    void reverseFastDecay(int speed);

};

#endif // MOTOR_H
