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
    armServo.write(ARM_HORIZONTAL);
    radarServo.write(RADAR_MID);
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
    delay(100);
    debug = display.prompt(F("ENABLE\nDEBUG?"));
    if (debug)
        driveModule.setSpeedScale(0.5);
    delay(100);
    display.printScn(F("Put robot\non track"));
    while (tape.update() != CENTER) {
        ;
    }
    display.printScn(F("  READY!\npress YES\nto begin"));
    delay(100);
    while (digitalRead(okBtn) == HIGH) {
        ;
    }
    display.printScn(F("\nSTARTING!"));
    delay(500);
    start();
}

void Robot::setSpeed(int speed) {
    setSpeed(speed, speed);
}

void Robot::setSpeed(int _lSpeed, int _rSpeed) {
    lSpeed = _lSpeed;
    rSpeed = _rSpeed;
}

void Robot::updateAnalogueSpeed(int * irAnalogue) {
    int lSpeed_ = constrain(map(irAnalogue[1] + irAnalogue[2], 0, 200, 0, 100), 0, 70);
    int rSpeed_ = constrain(map(irAnalogue[1] + irAnalogue[0], 0, 200, 0, 100), 0, 70);
    setSpeed(lSpeed_, rSpeed_);
}

bool Robot::update() {
    lastState = currentState;
    bool shelfTimeout = shelfMarkTimer.isActive();
    bool actionTimeout = actionTimer.isActive();
    updateLoopState = currentState.update(&lastState, tape.update(), shelfTimeout);

    if (!radar.pathClear()) {
        handleObstruction();
    } else if (updateLoopState == MARKER) {
        if (currentState.getState() == MARKER_HIGH) {
            if (!shelfTimeout) {
                shelfMarkTimer.setTimeOut(150);
            }
        }
        handleMarker();
        if (currentState.getState() == END)
            return true;
    } else if ((!shelfTimeout && !actionTimeout) || updateLoopState == CRITICAL) {
        // if there is no timeout active or state change was critical we enter the drive logic block
        drive();
    }
    if (debug) {
        displayState(stateToString(currentState.getState()), tape.stateToString(currentState.getTape()));
    }
    return false;
}

/** @brief Update the display with current speeds of the left and right motors, action and tape follower state. */
void Robot::displayState(String robotState, String tapeState) {
    display.reset();
    display.print(F("L: "));
    display.print(lSpeed);
    display.print(F("\nR: "));
    display.println(rSpeed);
    display.println(robotState);
    display.println(tapeState);
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
        case LEFT_CORNER:
            return F("L CORNER");
        case RIGHT_CORNER:
            return F("R CORNER");
        case MARKER_HIGH:
            return F("MARK HIGH");
        case MARKER_LOW:
            return F("MARK LOW");
        case LOST:
            return F("LOST");
        case END:
            return F("END");
        case SHELF:
            return F("SHELF");
        default:
            return F("ERROR");
    }
};

void Robot::calibrate() {
    delay(100);
    display.setTextSize(1);
    display.prompt(F("Place sensors ON tape\n\nPress SW3 when ready"));
    delay(100);
    tape.calibrateHigh();
    display.prompt(F("Place sensors OFF tape\n\nPress SW3 when ready"));
    delay(100);
    tape.calibrateLow();
    display.setTextSize(2);
    if (display.prompt(F("Save confg\nto EEPROM?")))
        tape.saveCalibrationToEEPROM();
    delay(100);
}

void Robot::start() {
    missionStartTimestamp = millis();
    driveModule.drive();
}

void Robot::handleObstruction() {
    driveModule.stop();
    while (!radar.pathClear()) {
        if (millis() - buzzerTimestamp > ALERT_LENGHT) {
            if (buzzing) {
                digitalWrite(buzzer, LOW);
                buzzing = false;
            } else {
                digitalWrite(buzzer, HIGH);
                buzzing = true;
            }
            buzzerTimestamp = millis();
        }
        if (!alertDisplayed) {
            display.printScn(F("   PLEASE\n   CLEAR\n    PATH"));
            alertDisplayed = true;
            radarServo.write(RADAR_LEFT);
            delay(400);
            radarServo.write(RADAR_RIGHT);
            delay(400);
            radarServo.write(RADAR_MID);
            delay(400);
        }

    }
    digitalWrite(buzzer, LOW);
    buzzing = false;
    alertDisplayed = false;
    display.printScn(F("\n DRIVING"));
    driveModule.drive();
}

void Robot::drive() {
    if (currentState.getState() == DRIVING) {
        updateAnalogueSpeed(tape.getIrAnalogue());
        driveModule.drive(lSpeed, rSpeed);
    } else if (currentState.getState() == RIGHT_CORNER) {
        if (lastState.getState() != RIGHT_CORNER) {
            driveModule.drive(20);
            actionTimer.setTimeOut(10);
        } else {
            driveModule.rotate(RIGHT);
        }
    } else if (currentState.getState() == LEFT_CORNER) {
        if (lastState.getState() != LEFT_CORNER) {
            driveModule.drive(20);
            actionTimer.setTimeOut(10);
        } else {
            driveModule.rotate(LEFT);
        }
    } else if (currentState.getState() == LOST) {
        /* if (lastState.getTape() == LEFT_EDGE || lastState.getState() == RIGHT_CORNER) {
            driveModule.rotate(RIGHT);
        } else if (lastState.getTape() == RIGHT_EDGE || lastState.getState() == LEFT_CORNER) {
            driveModule.rotate(LEFT);
        } else { */
        setSpeed(-20);
        driveModule.drive(lSpeed, rSpeed);
        actionTimer.setTimeOut(100);
    // }
    }
    /* if (currentState.getState() == RIGHT_CORNER)
        driveModule.rotate(RIGHT);
    if (currentState.getState() == LEFT_CORNER)
        driveModule.rotate(LEFT);*/
}

void Robot::handleMarker() {
    if (currentState.getState() == END) {
        driveModule.stop();
        display.printScn(F("\nFINISHED!"));
    } else if (currentState.getState() == SHELF) {
        driveModule.stop();
        display.printScn(F("\nMEASURING"));
        armServo.write(ARM_HORIZONTAL);
        delay(1000);
        armServo.write(ARM_VERTICAL);
        delay(1000);
        armServo.write(ARM_HORIZONTAL);
        delay(500);
        display.printScn(F("\n DRIVING"));
    } else {
        setSpeed(5);
        driveModule.drive(lSpeed, rSpeed);
    }
}

// TODO
void Robot::takeMeasurments() {

}
