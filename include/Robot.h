#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "Servo.h"
#include "Drive.h"
#include "State.h"
#include "Display.h"
#include "Radar.h"
#include "Tape.h"
#include "Colour.h"
#include "Definitions.h"
#include "Timer.h"

/**
 * @brief
 * Servo library uses Timer 1 that is also used for pwm on pins 9 & 10. Driving the H-Brigde requires 4 pwm signals.
 * Therefore the motors must be connected using pins 3,5,6,11 only. In addition to these restrictions, Arduino Uno
 * allows for interrupts only on pins 2 & 3, pin 3 is required for the H-Bridge, pin 2 should not be used for anything
 * in case interrupts are necessary.
 * Default pin connections:
 *  SCL, SDA                | A5, A4
 *  right motor IN3, IN4    | ~3, ~5
 *  left motor IN1, IN2     | ~11, ~6
 *  SW3(OK), SW2(CANCEL)    | 13, 12
 *  arm servo               | 7
 *  radar servo             | 8
 *  distance TRIG, ECHO     | 9, 10
 *  tape left, middle, right| A0, A1, A2
 *  buzzer                  | 4
 */
class Robot {
    friend class Controller;



private:
    uint8_t armServoPin = 7, radarServoPin = 8, trigPin = 9, echoPin = 10,
        lMotorIn1 = 11, lMotorIn2 = 6, rMotorIn3 = 3, rMotorIn4 = 5, okBtn = 13,
        cancelBtn = 12, buzzer = 4, tapeLeft = A0, tapeMid = A1, tapeRight = A2;

    uint32_t buzzerTimestamp = 0;
    uint32_t missionStartTimestamp = 0;
    uint32_t missionLength = 0;

    bool buzzing = false;
    bool alertDisplayed = false;

    int lSpeed = 0, rSpeed = 0;
    bool debug;
    int updateLoopState = 1;

    State currentState, lastState;

    Servo armServo, radarServo;
    Radar radar;
    Tape tape;
    Drive driveModule;
    Display display;
    Colour colour;
    Timer shelfMarkTimer;
    Timer finishMarkTimer;
    Timer actionTimer;

    void setSpeed(int speed);
    void setSpeed(int _lSpeed, int _rSpeed);
    void updateAnalogueSpeed(int * irAnalogue);
    void calibrate();
    void start();
    void handleObstruction();
    void drive();
    void handleMarker();
    void takeMeasurments();

public:
    Robot();
    void init();
    void update();
    void displayState(String robotState, String tapeState);
    String stateToString(uint8_t _robotState);

};


#endif // ROBOT_H