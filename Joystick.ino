#include "Keyboard.h"

enum Key {
    LWheelA = 2,
    LWheelB = 3,
    RWheelA = 0,
    RWheelB = 1,
    LWheelBtn = A2,
    RWheelBtn = A3,
    CLed = 4,
    LLedR = 5,
    LLedY = 6,
    LLedG = 7,
    RLedR = 8,
    RLedY = 9,
    RLedG = 10,
    SwitchA = 16,
    SwitchB = 14,
    SwitchC = 15,
    SwitchD = A0,
    SwitchE = A1,
};

#define INPORTS_CNT 11
uint8_t inPorts[] = {
    LWheelA, LWheelB,
    RWheelA, RWheelB,
    LWheelBtn, RWheelBtn,
    SwitchA, SwitchB, SwitchC, SwitchD, SwitchE
};
#define OUTPORTS_CNT 7
uint8_t outPorts[] = {
    CLed,
    LLedR, LLedY, LLedG,
    RLedR, RLedY, RLedG
};

bool stateLA = false, stateLB = false;
bool stateRA = false, stateRB = false;

void INT_LWheelA() {
    stateLA = true;
    if (stateLB) {
        // Clock
        Keyboard.write('s');
        stateLB = false;
        stateLA = false;
    }
}

void INT_LWheelB() {
    stateLB = true;
    if (stateLA) {
        // Anti-Clock
        Keyboard.write('w');
        stateLA = false;
        stateLB = false;
    }
}

void INT_RWheelA() {
    stateRA = true;
    if (stateRB) {
        // Clock
        Keyboard.write('d');
        stateRB = false;
        stateRA = false;
    }
}

void INT_RWheelB() {
    stateRB = true;
    if (stateRA) {
        // Anti-Clock
        Keyboard.write('a');
        stateRA = false;
        stateRB = false;
    }
}

void setup() {
    /*OUTPUT Mode*/
    for (uint8_t i = 0; i < OUTPORTS_CNT; i++)
        pinMode(outPorts[i], OUTPUT);
    
    /*INPUT Mode and PULLUP*/
    for (uint8_t i = 0; i < INPORTS_CNT; i++)
        pinMode(inPorts[i], INPUT_PULLUP);

    delay(1000);
    
    Keyboard.begin();

    /*Attach Interrupt*/
    
    attachInterrupt(digitalPinToInterrupt(LWheelA), &INT_LWheelA, FALLING);
    attachInterrupt(digitalPinToInterrupt(LWheelB), &INT_LWheelB, FALLING);
    attachInterrupt(digitalPinToInterrupt(RWheelA), &INT_RWheelA, FALLING);
    attachInterrupt(digitalPinToInterrupt(RWheelB), &INT_RWheelB, FALLING);
    
}

void loop() {
    digitalWrite(LLedY, !digitalRead(LWheelBtn));
    digitalWrite(RLedY, !digitalRead(RWheelBtn));  
}
