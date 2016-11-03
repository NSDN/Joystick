#include "Keyboard.h"

#define KEY_UP      3
#define KEY_LEFT    5
#define KEY_DOWN    7
#define KEY_RIGHT   6
#define KEY_L1      4
#define KEY_L2      2

#define KEY_A       A2
#define KEY_B       15
#define KEY_X       A0
#define KEY_Y       14
#define KEY_R1      A3
#define KEY_R2      A1

#define MODE_A      9
#define MODE_B      8
#define MODE_C      16
#define MODE_D      10

bool stateA = false, stateD = false;

void setup() {
    /*INPUT Mode*/
    pinMode(KEY_UP, INPUT);
    pinMode(KEY_LEFT, INPUT);
    pinMode(KEY_DOWN, INPUT);
    pinMode(KEY_RIGHT, INPUT);
    pinMode(KEY_L1, INPUT);
    pinMode(KEY_L2, INPUT);
    
    pinMode(KEY_A, INPUT);
    pinMode(KEY_B, INPUT);
    pinMode(KEY_X, INPUT);
    pinMode(KEY_Y, INPUT);
    pinMode(KEY_R1, INPUT);
    pinMode(KEY_R2, INPUT);

    pinMode(MODE_A, INPUT);
    pinMode(MODE_B, INPUT);
    pinMode(MODE_C, INPUT);
    pinMode(MODE_D, INPUT);
    
    /*PULL UP*/
    digitalWrite(KEY_UP, HIGH);
    digitalWrite(KEY_LEFT, HIGH);
    digitalWrite(KEY_DOWN, HIGH);
    digitalWrite(KEY_RIGHT, HIGH);
    digitalWrite(KEY_L1, HIGH);
    digitalWrite(KEY_L2, HIGH);
    
    digitalWrite(KEY_A, HIGH);
    digitalWrite(KEY_B, HIGH);
    digitalWrite(KEY_X, HIGH);
    digitalWrite(KEY_Y, HIGH);
    digitalWrite(KEY_R1, HIGH);
    digitalWrite(KEY_R2, HIGH);

    digitalWrite(MODE_A, HIGH);
    digitalWrite(MODE_B, HIGH);
    digitalWrite(MODE_C, HIGH);
    digitalWrite(MODE_D, HIGH);

    pinMode(0, OUTPUT);
    delay(1000);
    
    Keyboard.begin();
}

void loop() {
    if (!digitalRead(MODE_A)) {
        if (!stateA) {
            stateA = true;
            if (stateD) stateD = false;
            digitalWrite(0, HIGH);
            delay(250);
            digitalWrite(0, LOW);
        }
        
        if (digitalRead(KEY_LEFT) && digitalRead(KEY_DOWN)) Keyboard.release('d');
        else Keyboard.press('d');  
        if (digitalRead(KEY_UP) && digitalRead(KEY_RIGHT)) Keyboard.release('f');
        else Keyboard.press('f');
        if (digitalRead(KEY_A) && digitalRead(KEY_B)) Keyboard.release('j');
        else Keyboard.press('j');
        if (digitalRead(KEY_X) && digitalRead(KEY_Y)) Keyboard.release('k');
        else Keyboard.press('k');
        if (digitalRead(KEY_L1)) Keyboard.release('`');
        else Keyboard.press('`');
        if (digitalRead(KEY_R2)) Keyboard.release(KEY_ESC);
        else Keyboard.press(KEY_ESC);
        
    } else if (!digitalRead(MODE_D)) {
        if (!stateD) {
            stateD = true;
            if (stateA) stateA = false;
            digitalWrite(0, HIGH);
            delay(250);
            digitalWrite(0, LOW);
        }
        
        if (digitalRead(KEY_UP)) Keyboard.release(KEY_UP_ARROW);
        else Keyboard.press(KEY_UP_ARROW);
        if (digitalRead(KEY_DOWN)) Keyboard.release(KEY_DOWN_ARROW);
        else Keyboard.press(KEY_DOWN_ARROW);
        if (digitalRead(KEY_LEFT)) Keyboard.release(KEY_LEFT_ARROW);
        else Keyboard.press(KEY_LEFT_ARROW);  
        if (digitalRead(KEY_RIGHT)) Keyboard.release(KEY_RIGHT_ARROW);
        else Keyboard.press(KEY_RIGHT_ARROW);

        if (digitalRead(KEY_L1)) Keyboard.release(KEY_ESC);
        else Keyboard.press(KEY_ESC);
        if (digitalRead(KEY_R2)) Keyboard.release(KEY_RETURN);
        else Keyboard.press(KEY_RETURN);

        if (digitalRead(KEY_A)) Keyboard.release('z');
        else Keyboard.press('z');
        if (digitalRead(KEY_B)) Keyboard.release('z');
        else Keyboard.press('z');
        if (digitalRead(KEY_X)) Keyboard.release('x');
        else Keyboard.press('x');
        if (digitalRead(KEY_Y)) Keyboard.release('x');
        else Keyboard.press('x');
        if (digitalRead(KEY_L2)) Keyboard.release('c');
        else Keyboard.press('c');
        if (digitalRead(KEY_R1)) Keyboard.release('b');
        else Keyboard.press('b');

    } else {
        if (stateA || stateD) {
            stateA = stateD = false;
            digitalWrite(0, HIGH);
            delay(250);
            digitalWrite(0, LOW);
        }
        
        if (digitalRead(KEY_UP)) Keyboard.release(KEY_UP_ARROW);
        else Keyboard.press(KEY_UP_ARROW);
        if (digitalRead(KEY_DOWN)) Keyboard.release(KEY_DOWN_ARROW);
        else Keyboard.press(KEY_DOWN_ARROW);
        if (digitalRead(KEY_LEFT)) Keyboard.release(KEY_LEFT_ARROW);
        else Keyboard.press(KEY_LEFT_ARROW);  
        if (digitalRead(KEY_RIGHT)) Keyboard.release(KEY_RIGHT_ARROW);
        else Keyboard.press(KEY_RIGHT_ARROW);
    
        if (digitalRead(KEY_A)) Keyboard.release('z');
        else Keyboard.press('z');
        if (digitalRead(KEY_B)) Keyboard.release('x');
        else Keyboard.press('x');
        if (digitalRead(KEY_X)) Keyboard.release('a');
        else Keyboard.press('a');
        if (digitalRead(KEY_Y)) Keyboard.release('s');
        else Keyboard.press('s');
        if (digitalRead(KEY_R1)) Keyboard.release('c');
        else Keyboard.press('c');
        if (digitalRead(KEY_R2)) Keyboard.release('d');
        else Keyboard.press('d');

        if (digitalRead(KEY_L1)) Keyboard.release(KEY_ESC);
        else Keyboard.press(KEY_ESC);
        if (digitalRead(KEY_L2)) Keyboard.release(KEY_RETURN);
        else Keyboard.press(KEY_RETURN);
        
    }
}
