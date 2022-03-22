#include <Arduino.h>
#include <Servo.h>
Servo armServo;
Servo radarServo;
void setup() {
    armServo.attach(7);
    radarServo.attach(8);
}
int arm = 0;
int radar = 0;
int armLowerBound = 175;
int armHigherBound = 70;
int radarLowerBound = 20;
int radarHigherBound = 155;

void loop() {
    for (size_t i = 0; i < 100; i++) {
        arm = map(i, 0, 100, armLowerBound, armHigherBound);
        radar = map(i, 0, 100, radarLowerBound, radarHigherBound);
        armServo.write(arm);
        radarServo.write(radar);
        delay(50);
    }
    for (size_t i = 100; i > 0; i--) {
        arm = map(i, 0, 100, armLowerBound, armHigherBound);
        radar = map(i, 0, 100, radarLowerBound, radarHigherBound);
        armServo.write(arm);
        radarServo.write(radar);
        delay(50);
    }
}