#include "Robot.h"

Robot::Robot()
    : radar(trigPin, echoPin),
    tape(tapeLeft, tapeMid, tapeRight),
    driveModule(new Motor(rMotorIn3, rMotorIn4), new Motor(lMotorIn2, lMotorIn1)),
    display(okBtn, cancelBtn) {
}

void Robot::init() {
    // initialize all modules
    pinMode(buzzer, OUTPUT);
    digitalWrite(buzzer, LOW);
    armServo.attach(armServoPin);
    radarServo.attach(radarServoPin);
    display.init();
    colour.init();
    tape.init();
    driveModule.init();

    // user prompts
    if (display.prompt(F("Calibrate?"))) { // Prompt the user if calibration is required
        calibrate();
    } else if (!tape.checkEEPROM()) { // if calibration wasn't carried out check EEPROM for saved calibrations
        calibrate();
    } else {
        tape.readCalibrationFromEEPROM(); // calibration data found, load calibration
    }
    debug = display.prompt(F("ENABLE\nDEBUG?"));
    display.printScn(F("Put robot\non track"));
    while (currentState.getTape() != CENTER) {
        tape.update();
    }
    display.printScn(F("  READY!\npress YES\nto begin"));
    while (digitalRead(okBtn) == HIGH) {
        ;
    }
    display.printScn(F("\nSTARTING!"));
    delay(500);
}

void Robot::setSpeed(int speed) {
    setSpeed(speed, speed);
}

void Robot::setSpeed(int _lSpeed, int _rSpeed) {
    lSpeed = _lSpeed * speedScale;
    rSpeed = _rSpeed * speedScale;
}

void Robot::updateAnalogueSpeed() {
    int * irAnalogue = new int[3];
    irAnalogue = tape.getIrAnalogue();
    lSpeed = constrain(map(irAnalogue[1] + irAnalogue[2], 0, 200, 0, 100), 0, 100);
    rSpeed = constrain(map(irAnalogue[1] + irAnalogue[0], 0, 200, 0, 100), 0, 100);
    delete(irAnalogue);
}

void Robot::update() {
    lastState = currentState;
    currentState.update(&lastState, tape.update());

    // NOTE if this section gets too long it should be refactored into seperate functions or even class
    if (currentState.getState() == DRIVING) {
        updateAnalogueSpeed();
        driveModule.drive(lSpeed, rSpeed);
    }

    if (currentState.getState() == LOST) {
        if (lastState.getTape() == LEFT_EDGE) {
            driveModule.rotate(RIGHT);
        } else if (lastState.getTape() == RIGHT_EDGE) {
            driveModule.rotate(LEFT);
        } else if (lastState.getTape() == MARKER) {
            setSpeed(40);
            driveModule.drive(lSpeed, rSpeed);
        } else if (lastState.getTape() == CENTER) {
            updateAnalogueSpeed();
            driveModule.drive(lSpeed, rSpeed);
        } else {
            setSpeed(-40);
            driveModule.drive(lSpeed, rSpeed);
        }
    }

    if (debug)
        displayState();

}

/** @brief Update the display with current speeds of the left and right motors, action and tape follower state. */
void Robot::displayState() {
    char buffer[20];
    sprintf(buffer, "L: %d\nR: %d", lSpeed, rSpeed);
    display.reset();
    display.println(stateToString(currentState.getState()));
    display.println(tape.stateToString(currentState.getTape()));
    display.println(buffer);
    display.display();
}

/**
 * @brief Get a string from the robot state
 * @param _robotState robot state enum
 * @return String representation of the robot state
 */
String Robot::stateToString(uint8_t _robotState) {
    switch (_robotState) {
        case DRIVING:
            return F("DRIVING");
        case LOST:
            return F("LOST");
        case END:
            return F("END");
        case SHELF_COLOUR_CHECK:
            return F("COLOR CHK");
        case SHELF_WEIGHT_CHECK:
            return F("WEIGHT CHK");
        case OBSTACLE:
            return F("OBSTACLE");
        default:
            return F("ERROR");
    }
};

void Robot::calibrate() {
    display.setTextSize(1);
    display.prompt(F("Place sensors ON tape\n\nPress SW3 when ready"));
    tape.calibrateHigh();
    display.prompt(F("Place sensors OFF tape\n\nPress SW3 when ready"));
    tape.calibrateLow();
    display.setTextSize(2);
}