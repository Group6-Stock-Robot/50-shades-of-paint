#include "State.h"
#include "Definitions.h"

State::State()
    : tape(UNDEFINED_STATE),
    state(UNDEFINED_STATE),
    lastKnownTape(UNDEFINED_STATE) {
}


uint8_t State::update(State * lastState, uint8_t _tape, bool markerTimeoutActive) {
    tape = _tape;
    if (_tape == CENTER || _tape == LEFT_EDGE || _tape == RIGHT_EDGE) {
        lastKnownTape = _tape;
        if (markerTimeoutActive) {
            return MARKER;
        } else {
            state = DRIVING;
            if (lastState->getState() == LOST || lastState->getState() == RIGHT_CORNER || lastState->getState() == LEFT_CORNER) {
                /* if (tape == LEFT_EDGE)
                    state = RIGHT_CORNER;
                else if (tape == RIGHT_EDGE)
                    state = LEFT_CORNER;
                else
                    state = DRIVING; */
                return CRITICAL;
            } else {
                // state = DRIVING;
                return NON_CRITICAL;
            }
        }
    }

    if (_tape == LOST_TAPE) {
        if (markerTimeoutActive) {
            state = MARKER_LOW;
            return MARKER;
        } else {
            if (lastState->getState() == MARKER_HIGH || lastState->getState() == MARKER_LOW) {
                if (lastKnownTape == LEFT_EDGE)
                    state = RIGHT_CORNER;
                if (lastKnownTape == RIGHT_EDGE)
                    state = LEFT_CORNER;
                return CRITICAL;
            } else if (lastState->getTape() == LEFT_EDGE || lastState->getState() == RIGHT_CORNER) {
                state = RIGHT_CORNER;
            } else if (lastState->getTape() == RIGHT_EDGE || lastState->getState() == LEFT_CORNER) {
                state = LEFT_CORNER;
            } else {
                state = LOST;
                return CRITICAL;
            }
        }
        if (lastState->getState() == DRIVING)
            return CRITICAL;
        else
            return NON_CRITICAL;
    }

    if (_tape == MARK) {
        if (lastState->getState() == MARKER_LOW && markerTimeoutActive) {
            state = SHELF;
            return MARKER;
        } else if (lastState->getState() == MARKER_HIGH && !markerTimeoutActive) {
            state = END;
            return MARKER;
        } else if ((lastState->getState() == LEFT_CORNER || lastState->getState() == RIGHT_CORNER || lastState->getState() == LOST) && !markerTimeoutActive) {
            state = LOST;
            return NON_CRITICAL;
        }
        state = MARKER_HIGH;
        return MARKER;
    }
    return UNDEFINED_STATE;
}

State State::operator=(State & source) {
     // Guard self assignment
    if (this == &source)
        return *this;

    tape = source.tape;
    state = source.state;
    return *this;
}

bool State::operator ==(State & compareState) {
    return(tape == compareState.tape && state == compareState.state);
}
