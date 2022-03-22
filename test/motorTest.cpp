#include <Arduino.h>
#include "Motor.h"

Motor rightMotor(3, 5);
Motor leftMotor(6, 11);
void setup() {
    rightMotor.init();
    leftMotor.init();
}

void loop() {
    for (int i = 0; i < 100; i++) {
        rightMotor.forward(i);
        delay(20);
    }
    rightMotor.stop();
    for (int i = 0; i < 100; i++) {
        rightMotor.reverse(i);
        delay(20);
    }
    rightMotor.stop();
    for (int i = 0; i < 100; i++) {
        leftMotor.forward(i);
        delay(20);
    }
    leftMotor.stop();
    for (int i = 0; i < 100; i++) {
        leftMotor.reverse(i);
        delay(20);
    }
    leftMotor.stop();
    delay(2000);
}