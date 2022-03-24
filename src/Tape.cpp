#include "Tape.h"
#include <EEPROM.h>
#include "Definitions.h"

Tape::Tape(uint8_t _irLeft, uint8_t _irCenter, uint8_t _irRight) {
    irPins[0] = _irLeft;
    irPins[1] = _irCenter;
    irPins[2] = _irRight;
}

void Tape::init() {
    for (size_t i = 0; i < 3; i++) {
        pinMode(irPins[i], INPUT);
        irBinary[i] = digitalRead(irPins[i]);
    } // set pinMode to INPUT for diodes
}

uint8_t Tape::update() {
    updateDigital();
    return defineState();
}

String Tape::stateToString(uint8_t _state) {
    switch (_state) {
        case CENTER:
            return F("CENTER");
        case LEFT_EDGE:
            return F("LEFT_EDGE");
        case RIGHT_EDGE:
            return F("RIGHT_EDGE");
        case LOST_TAPE:
            return F("LOST TAPE");
        case MARK:
            return F("MARK");
        default:
            return F("ERROR");
    }
}

uint8_t Tape::defineState() {
    if (irBinary[0] == LOW && irBinary[2] == LOW) {
        if (irBinary[1] == LOW) // Robot is off of the tape
            return LOST_TAPE;
        else // Robot centered on tape
            return CENTER;
    }
    // Robot is on the right edge of the tape
    if (irBinary[0] == HIGH && irBinary[2] == LOW) {
        return RIGHT_EDGE;
    }
    // Robot is on the left edge of the tape
    if (irBinary[0] == LOW && irBinary[2] == HIGH) {
        return LEFT_EDGE;
    }
    // Robot either on the shelf mark, finish line or perpendicular to the track
    if (irBinary[0] == HIGH && irBinary[1] == HIGH && irBinary[2] == HIGH) {
        return MARK;
    }
    return UNDEFINED_STATE;
}

uint8_t * Tape::updateDigital() {
    irBinary[0] = digitalRead(irPins[0]);
    irBinary[1] = digitalRead(irPins[1]);
    irBinary[2] = digitalRead(irPins[2]);
    return irBinary;
}

int * Tape::updateAnalogue() {
    irAnalogue[0] = constrain(map(analogRead(irPins[0]), analogLowCal[0], analogHighCal[0], 0, 100), 0, 100);
    irAnalogue[1] = constrain(map(analogRead(irPins[1]), analogLowCal[1], analogHighCal[1], 0, 100), 0, 100);
    irAnalogue[2] = constrain(map(analogRead(irPins[2]), analogLowCal[2], analogHighCal[2], 0, 100), 0, 100);
    return irAnalogue;
}

uint16_t * Tape::calibrate(uint16_t * analogCalArray) {
    int count = 1;
    int l = 0;
    int m = 0;
    int r = 0;
    for (; count <= 1000; count++) {
        l = analogRead(A0);
        m = analogRead(A1);
        r = analogRead(A2);
        // calculate moving average 
        analogCalArray[0] = (analogCalArray[0] - (analogCalArray[0] * 1 / count)) + (l / count);
        analogCalArray[1] = (analogCalArray[1] - (analogCalArray[1] * 1 / count)) + (m / count);
        analogCalArray[2] = (analogCalArray[2] - (analogCalArray[2] * 1 / count)) + (r / count);
    }
    return analogCalArray;
}

uint16_t * Tape::calibrateHigh() {
    return calibrate(analogHighCal);
}

uint16_t * Tape::calibrateLow() {
    return calibrate(analogLowCal);
}



bool Tape::checkEEPROM() {
    if ((char) EEPROM.read(0) == '$') {
        return true;
    }
    return false;
}

void Tape::saveCalibrationToEEPROM() {
    int address = 0;
    EEPROM.put(address, '$');
    address += sizeof(char);
    EEPROM.put(address, analogHighCal[0]);
    address += sizeof(uint16_t);
    EEPROM.put(address, analogHighCal[1]);
    address += sizeof(uint16_t);
    EEPROM.put(address, analogHighCal[2]);
    address += sizeof(uint16_t);
    EEPROM.put(address, analogLowCal[0]);
    address += sizeof(uint16_t);
    EEPROM.put(address, analogLowCal[1]);
    address += sizeof(uint16_t);
    EEPROM.put(address, analogLowCal[2]);
}

void Tape::readCalibrationFromEEPROM() {
    int address = 0;
    address += sizeof(char);
    analogHighCal[0] = EEPROM.get(address, analogHighCal[0]);
    address += sizeof(uint16_t);
    analogHighCal[1] = EEPROM.get(address, analogHighCal[1]);
    address += sizeof(uint16_t);
    analogHighCal[2] = EEPROM.get(address, analogHighCal[2]);
    address += sizeof(uint16_t);
    analogLowCal[0] = EEPROM.get(address, analogLowCal[0]);
    address += sizeof(uint16_t);
    analogLowCal[1] = EEPROM.get(address, analogLowCal[1]);
    address += sizeof(uint16_t);
    analogLowCal[2] = EEPROM.get(address, analogLowCal[2]);
}
