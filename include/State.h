#ifndef STATE_H
#define STATE_H
#include <Arduino.h>

class State {
private:
    uint8_t tape;
    // uint8_t motor;
    uint8_t state;
    uint8_t lastKnownTape;

public:
    State();

    uint8_t update(State * lastState, uint8_t tape, bool markerTimeoutActive);
    State operator =(State & source);
    bool operator ==(State & compareState);

    uint8_t getTape() { return tape; }
    void setTape(uint8_t tape_) { tape = tape_; }

    uint8_t getState() { return state; }
    void setState(uint8_t state_) { state = state_; }
};


#endif // STATE_H
