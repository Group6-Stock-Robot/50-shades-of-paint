#include "Timer.h"

Timer::Timer()
    : timeStamp(0),
    timeOut(0),
    active(false) {
}

void Timer::setTimeOut(uint32_t timeOut_) {
    timeOut = timeOut_;
    active = true;
    timeStamp = millis();
}

bool Timer::isActive() {
    if (active) {
        active = (millis() - timeStamp) < timeOut;
        return active;
    } else {
        return false;
    }
}
