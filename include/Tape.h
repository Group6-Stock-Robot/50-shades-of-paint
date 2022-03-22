#ifndef TAPE_H
#define TAPE_H
#include <Arduino.h>

/**
 * @brief
 * Class representing the Tape follower module of the robot.
 * @details
 * Contains the pin numbers of diodes, their digital and analogue values.
 * Provides an enumerated state constants used to represent the state of the module.
 * On first use it needs to be calibrated. The calibration values can optionally be
 * saved to the Uno's EEPROM providing a non-volatile storage that can be reused on
 * subsequent power cycles.
 */
class Tape {

    /** @brief irX[0] holds state for left, irX[1] center and irX[2] right diode.*/
    uint8_t irPins[3];
    uint8_t irBinary[3];
    int irAnalogue[3];
    uint16_t analogHighCal[3] = { 0, 0, 0 };
    uint16_t analogLowCal[3] = { 0, 0, 0 };

public:
    Tape(uint8_t _irLeft = A0, uint8_t _irCenter = A1, uint8_t _irRight = A2);
    void init();
    uint8_t update();
    int * getIrAnalogue() { return updateAnalogue(); }

    uint16_t * calibrateHigh();
    uint16_t * calibrateLow();
    bool checkEEPROM();
    void saveCalibrationToEEPROM();
    void readCalibrationFromEEPROM();
    String stateToString(uint8_t _state);

private:
    uint16_t * calibrate(uint16_t * analogCalArray);
    uint8_t defineState();
    uint8_t * updateDigital();
    int * updateAnalogue();


};


#endif // TAPE_H
