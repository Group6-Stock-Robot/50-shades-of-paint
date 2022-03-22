#include <Arduino.h>
#include <Servo.h>
#include <Ultrasonic.h>

Servo radarServo;
Ultrasonic ruler(9, 10);

void setup() {
    radarServo.attach(8);
    Serial.begin(9600);
}

int radar = 0;
int radarLowerBound = 20;
int radarHigherBound = 155;
int distance = 0;

void loop() {
    for (size_t i = 0; i < 100; i++) {
        radar = map(i, 0, 100, radarLowerBound, radarHigherBound);
        radarServo.write(radar);
        distance = ruler.read();
        Serial.print(radar);
        Serial.print("deg: ");
        Serial.print(distance);
        Serial.println("cm");
        delay(50);
    }
    for (size_t i = 100; i > 0; i--) {
        radar = map(i, 0, 100, radarLowerBound, radarHigherBound);
        radarServo.write(radar);
        distance = ruler.read();
        Serial.print(radar);
        Serial.print("deg: ");
        Serial.print(distance);
        Serial.println("cm");
        delay(50);
    }
}