
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define UNDEFINED_STATE -1
#define LEFT 0
#define RIGHT 1


#define NON_CRITIAL 0
#define CRITICAL 1
#define MARKER 2
#define FINISH 3

#define ARM_HORIZONTAL 176
#define ARM_VERTICAL 80
#define RADAR_OFFSET -3
#define RADAR_LEFT 45 + RADAR_OFFSET
#define RADAR_MID 90 + RADAR_OFFSET
#define RADAR_RIGHT 135 + RADAR_OFFSET
#define ALERT_LENGHT 700

/** @brief Sensor state representation */
enum TapeState {
    CENTER,
    LEFT_EDGE,
    RIGHT_EDGE,
    LOST_TAPE,
    MARK
};

enum MotorState {
    FORWARD,
    REVERSE,
    STOP,
    ROTATE,
    TURN_AROUND
};

enum RobotState {
    DRIVING,
    LEFT_CORNER,
    RIGHT_CORNER,
    MARKER_HIGH,
    MARKER_LOW,
    SHELF,
    LOST,
    END
};

#endif // DEFINITIONS_H
