#include "Colour.h"

Colour::Colour() : Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X) {
}

bool Colour::init() {
    if (Adafruit_TCS34725::begin()) {
        return true;
    }
    return false;
}

uint16_t * Colour::update() {
    Adafruit_TCS34725::getRawData(&rgbc[0], &rgbc[1], &rgbc[2], &rgbc[3]);
    colorTemp = Adafruit_TCS34725::calculateColorTemperature_dn40(rgbc[0], rgbc[1], rgbc[2], rgbc[3]);
    lux = calculateLux(rgbc[0], rgbc[1], rgbc[2]);
    return rgbc;
}

void Colour::debug() {
    if (!Serial) {
        Serial.begin(9600);
    }
    Serial.print(F("Color Temp: ")); Serial.print(colorTemp, DEC); Serial.print(F(" K - "));
    Serial.print(F("Lux: ")); Serial.print(lux, DEC); Serial.print(F(" - "));
    Serial.print(F("R: ")); Serial.print(rgbc[0], DEC); Serial.print(F(" "));
    Serial.print(F("G: ")); Serial.print(rgbc[1], DEC); Serial.print(F(" "));
    Serial.print(F("B: ")); Serial.print(rgbc[2], DEC); Serial.print(F(" "));
    Serial.print(F("C: ")); Serial.print(rgbc[3], DEC); Serial.print(F(" "));
    Serial.println();
}
