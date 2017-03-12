#include "Keyboard.h"
#include "Mouse.h"

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

enum State {
    Keybd,
    Mise,
    Etc
} state;
 
#define DELAY_TIM 50

void INT_LWheel() {
    delay(DELAY_TIM);
    if (digitalRead(LWheelB) == LOW) {
        if (digitalRead(LWheelA) == LOW) {
            // Clock
            if (state == Keybd) Keyboard.write('j');
            else if (state == Mise) Mouse.move(0, 5, 0);
        }
    } else {
        if (digitalRead(LWheelA) == LOW) {
            // Anti-Clock
            if (state == Keybd) Keyboard.write('u');
            else if (state == Mise) Mouse.move(0, -5, 0);
        }
    }
}

void INT_RWheel() {
    delay(DELAY_TIM);
    if (digitalRead(RWheelB) == LOW) {
        if (digitalRead(RWheelA) == LOW) {
            // Clock
            if (state == Keybd) Keyboard.write('k');
            else if (state == Mise) Mouse.move(5, 0, 0);
        }
    } else {
        if (digitalRead(RWheelA) == LOW) {
            // Anti-Clock
            if (state == Keybd) Keyboard.write('h');
            else if (state == Mise) Mouse.move(-5, 0, 0);
        }
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
    Mouse.begin();

    /*Attach Interrupt*/
    
    attachInterrupt(digitalPinToInterrupt(LWheelA), &INT_LWheel, CHANGE);
    attachInterrupt(digitalPinToInterrupt(RWheelA), &INT_RWheel, CHANGE);
    
}
bool led = false;

void loop() {
    digitalWrite(CLed, led);
    led = !led;
    
    if (digitalRead(SwitchE) == HIGH) {
        state = Keybd;
    } else {
        state = Mise;
    }
    
    if (!digitalRead(LWheelBtn)) {
        if (state == Keybd) {
            while (!digitalRead(LWheelBtn));
            Keyboard.write('y');
        } else if (state == Mise) {
            if (!Mouse.isPressed(MOUSE_LEFT)) {
                Mouse.press(MOUSE_LEFT);
            }
        }
    } else {
        if (state == Mise) {
            if (Mouse.isPressed(MOUSE_LEFT)) {
                Mouse.release(MOUSE_LEFT);
            }
        }
    }
    if (!digitalRead(RWheelBtn)) {
        if (state == Keybd) {
            while (!digitalRead(RWheelBtn));
            Keyboard.write('i');
        } else if (state == Mise) {
            if (!Mouse.isPressed(MOUSE_RIGHT)) {
                Mouse.press(MOUSE_RIGHT);
            }
        }
    } else {
        if (state == Mise) {
            if (Mouse.isPressed(MOUSE_RIGHT)) {
                Mouse.release(MOUSE_RIGHT);
            }
        }
    }

    digitalWrite(LLedG, !digitalRead(LWheelA));
    digitalWrite(LLedY, !digitalRead(LWheelBtn));
    digitalWrite(LLedR, !digitalRead(LWheelB));
    digitalWrite(RLedR, !digitalRead(RWheelA));
    digitalWrite(RLedY, !digitalRead(RWheelBtn));
    digitalWrite(RLedG, !digitalRead(RWheelB));
}
