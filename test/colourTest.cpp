#include <Arduino.h>

#include <Colour.h>

Colour colour;

void setup() {
    Serial.begin(9600);
    colour.init();
}


void loop() {
    colour.update();
    Serial.print("RGB:");
    Serial.print(colour.getR());
    Serial.print(", ");
    Serial.print(colour.getG());
    Serial.print(", ");
    Serial.println(colour.getB());
    Serial.print("Lux: ");
    Serial.print(colour.getLux());
    Serial.print(", Tmp: ");
    Serial.println(colour.getColorTemp());
    delay(500);
}