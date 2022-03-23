#include "State.h"
#include "Definitions.h"

State::State()
    : tape(UNDEFINED_STATE),
    state(UNDEFINED_STATE) {
}

State * State::update(State * lastState, uint8_t _tape) {
    tape = _tape;
    if (lastState->getState() == SHELF_COLOUR_CHECK) {
        state = SHELF_WEIGHT_CHECK;
    } else if (lastState->getState() == SHELF_WEIGHT_CHECK) {
        state = DRIVING;
    } else {
        if (tape == CENTER || tape == LEFT_EDGE || tape == RIGHT_EDGE) {
            state = DRIVING;
        }
        if (tape == LOST_TAPE) {
            if (lastState->getState() == LEFT_EDGE || lastState->getState() == RIGHT_CORNER)
                state = RIGHT_CORNER;
            else if (lastState->getState() == RIGHT_EDGE || lastState->getState() == LEFT_CORNER)
                state = LEFT_CORNER;
            else
                state = LOST;
        }
        if (tape == MARKER) {
            if (lastState->getState() != LOST)
                state = SHELF_COLOUR_CHECK;
            else
                state = LOST;
        }
    }
    return this;
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
