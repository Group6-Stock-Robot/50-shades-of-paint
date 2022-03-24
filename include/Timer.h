#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
private:
    uint32_t timeStamp;
    uint32_t timeOut;
    bool active;

public:
    Timer();
    uint32_t getTimeStamp() const { return timeStamp; }
    uint32_t getTimeOut() const { return timeOut; }
    void setTimeOut(uint32_t timeOut_);
    bool isActive();

};

#endif // TIMER_H
