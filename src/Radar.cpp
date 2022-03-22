#include "Radar.h"

Radar::Radar(uint8_t trigger, uint8_t echo) : Ultrasonic(trigger, echo) {}

uint32_t Radar::update() {
    distance = Ultrasonic::read();
    return distance;
}
