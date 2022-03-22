#ifndef COLOUR_H
#define COLOUR_H

#include <Adafruit_TCS34725.h>

class Colour : public Adafruit_TCS34725 {
private:
    uint16_t colorTemp, lux;
    uint16_t rgbc[4];
public:
    Colour();
    bool init();
    uint16_t * update();
    void debug();

    uint16_t getLux() { return lux; };
    uint16_t getColorTemp() { return colorTemp; };
    uint16_t * getRGB() { return rgbc; };
    uint16_t getR() { return rgbc[0]; };
    uint16_t getG() { return rgbc[1]; };
    uint16_t getB() { return rgbc[2]; };
    uint16_t getC() { return rgbc[3]; };
};

#endif // COLOUR_H
