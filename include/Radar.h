#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <Arduino.h>
#include <Ultrasonic.h>

class Radar : public Ultrasonic {
private:
    const uint8_t shelfDistance = 20;
    const uint8_t alertThreshold = 50;
    uint32_t distance;
public:
    Radar(uint8_t trigger, uint8_t echo);
    uint32_t update();
    int getDistance() { return distance; }
};



#endif // OBSTACLE_H
