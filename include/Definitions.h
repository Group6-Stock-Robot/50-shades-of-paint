
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define UNDEFINED_STATE -1
#define LEFT 0
#define RIGHT 1

/** @brief Sensor state representation */
enum TapeState {
    CENTER,
    LEFT_EDGE,
    RIGHT_EDGE,
    LEFT_CORNER,
    RIGHT_CORNER,
    LOST_TAPE,
    MARKER
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
    LOST,
    END,
    SHELF_COLOUR_CHECK,
    SHELF_WEIGHT_CHECK,
    OBSTACLE
};

#endif // DEFINITIONS_H
