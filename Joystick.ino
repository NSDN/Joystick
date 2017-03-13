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
    Mise = 0x00,
    
    Keybd = 0x10,   FunA = 0x01,
    Touhou = 0x20,  FunB = 0x02,
    Etc1 = 0x40,    FunC = 0x04,
    Etc2 = 0x80,    FunD = 0x08   
};
uint8_t state;
 
#define DELAY_TIM 50

void INT_LWheel() {
    delay(DELAY_TIM);
    if (digitalRead(LWheelB) == LOW) {
        if (digitalRead(LWheelA) == LOW) {
            // Clock
            if ((state & 0xF0) == Keybd) Keyboard.write('j');
            else if ((state & 0xF0) == Mise) Mouse.move(0, 5, 0);
            else if ((state & 0xF0) == Touhou) Keyboard.write(KEY_DOWN_ARROW); 
        }
    } else {
        if (digitalRead(LWheelA) == LOW) {
            // Anti-Clock
            if ((state & 0xF0) == Keybd) Keyboard.write('u');
            else if ((state & 0xF0) == Mise) Mouse.move(0, -5, 0);
            else if ((state & 0xF0) == Touhou) Keyboard.write(KEY_UP_ARROW);
        }
    }
}

void INT_RWheel() {
    delay(DELAY_TIM);
    if (digitalRead(RWheelB) == LOW) {
        if (digitalRead(RWheelA) == LOW) {
            // Clock
            if ((state & 0xF0) == Keybd) Keyboard.write('k');
            else if ((state & 0xF0) == Mise) Mouse.move(5, 0, 0);
            else if ((state & 0xF0) == Touhou) Keyboard.write(KEY_RIGHT_ARROW);
        }
    } else {
        if (digitalRead(RWheelA) == LOW) {
            // Anti-Clock
            if ((state & 0xF0) == Keybd) Keyboard.write('h');
            else if ((state & 0xF0) == Mise) Mouse.move(-5, 0, 0);
            else if ((state & 0xF0) == Touhou) Keyboard.write(KEY_LEFT_ARROW);
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

bool lock = false;

void getState() {
    if (!digitalRead(SwitchB)) {
        state |= (Keybd >> 4);
    } else {
        state &= ~(Keybd >> 4);
    }
    if (!digitalRead(SwitchC)) {
        state |= (Touhou >> 4);
    } else {
        state &= ~(Touhou >> 4);
    }
    if (!digitalRead(SwitchD)) {
        state |= (Etc1 >> 4);
    } else {
        state &= ~(Etc1 >> 4);
    }
    if (!digitalRead(SwitchE)) {
        state |= (Etc2 >> 4);
    } else {
        state &= ~(Etc2 >> 4);
    }
}

void loop() {
    if (!digitalRead(SwitchA)) {
        if (!lock) {
            lock = true;
            state = state << 4;
            getState();
            while ((state & 0x0F) > 0) {
                getState();
            }
            digitalWrite(CLed, HIGH);
            if (state > 0x80) state &= 0x0F;
        }
    } else {
        if (lock) {
            lock = false;
            state &= 0x0F;
            digitalWrite(CLed, LOW);
        }
    }

    getState();
    
    if (!digitalRead(LWheelBtn)) {
        if ((state & 0xF0) == Keybd) {
            while (!digitalRead(LWheelBtn));
            Keyboard.write('y');
        } else if ((state & 0xF0) == Mise) {
            if (!Mouse.isPressed(MOUSE_LEFT)) {
                Mouse.press(MOUSE_LEFT);
            }
        } else if ((state & 0xF0) == Touhou) {
            while (!digitalRead(RWheelBtn));
            Keyboard.write(KEY_ESC);
        }
    } else {
        if ((state & 0xF0) == Mise) {
            if (Mouse.isPressed(MOUSE_LEFT)) {
                Mouse.release(MOUSE_LEFT);
            }
        }
    }
    if (!digitalRead(RWheelBtn)) {
        if ((state & 0xF0) == Keybd) {
            while (!digitalRead(RWheelBtn));
            Keyboard.write('i');
        } else if ((state & 0xF0) == Mise) {
            if (!Mouse.isPressed(MOUSE_RIGHT)) {
                Mouse.press(MOUSE_RIGHT);
            }
        } else if ((state & 0xF0) == Touhou) {
            while (!digitalRead(RWheelBtn));
            Keyboard.write(KEY_RETURN);
        }
    } else {
        if ((state & 0xF0) == Mise) {
            if (Mouse.isPressed(MOUSE_RIGHT)) {
                Mouse.release(MOUSE_RIGHT);
            }
        }
    }

    if ((state & 0xF0) > 0) {
        if ((state & FunA) > 0) {
            Keyboard.write('z');
        }
        if ((state & FunB) > 0) {
            Keyboard.write('x');
        }
        if ((state & FunC) > 0) {
            Keyboard.write('c');
        }
        if ((state & FunD) > 0) {
            Keyboard.write('v');
        }
    }

    digitalWrite(LLedG, !digitalRead(LWheelA));
    digitalWrite(LLedY, !digitalRead(LWheelBtn));
    digitalWrite(LLedR, !digitalRead(LWheelB));
    digitalWrite(RLedR, !digitalRead(RWheelA));
    digitalWrite(RLedY, !digitalRead(RWheelBtn));
    digitalWrite(RLedG, !digitalRead(RWheelB));
}
