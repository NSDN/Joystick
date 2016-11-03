#include "Keyboard.h"

#define KEY_UP      2
#define KEY_LEFT    3
#define KEY_DOWN    4
#define KEY_RIGHT   5
#define KEY_L       6
#define KEY_A       A3
#define KEY_B       A0
#define KEY_X       A2
#define KEY_Y       A1
#define KEY_R       15

bool isOSU = false;

void setup() {
    /*INPUT Mode*/
    pinMode(KEY_UP, INPUT);
    pinMode(KEY_LEFT, INPUT);
    pinMode(KEY_DOWN, INPUT);
    pinMode(KEY_RIGHT, INPUT);
    pinMode(KEY_L, INPUT);
    pinMode(KEY_A, INPUT);
    pinMode(KEY_B, INPUT);
    pinMode(KEY_X, INPUT);
    pinMode(KEY_Y, INPUT);
    pinMode(KEY_R, INPUT);
    /*PULL UP*/
    digitalWrite(KEY_UP, HIGH);
    digitalWrite(KEY_LEFT, HIGH);
    digitalWrite(KEY_DOWN, HIGH);
    digitalWrite(KEY_RIGHT, HIGH);
    digitalWrite(KEY_L, HIGH);
    digitalWrite(KEY_A, HIGH);
    digitalWrite(KEY_B, HIGH);
    digitalWrite(KEY_X, HIGH);
    digitalWrite(KEY_Y, HIGH);
    digitalWrite(KEY_R, HIGH);

    delay(500);
    if (!digitalRead(KEY_L) && !digitalRead(KEY_R)) {
        isOSU = true;
    }
    
    Keyboard.begin();
}

void loop() {
    if (isOSU) {
        if (digitalRead(KEY_LEFT) && digitalRead(KEY_DOWN)) Keyboard.release('d');
        else Keyboard.press('d');  
        if (digitalRead(KEY_UP) && digitalRead(KEY_RIGHT)) Keyboard.release('f');
        else Keyboard.press('f');
        if (digitalRead(KEY_A) && digitalRead(KEY_B)) Keyboard.release('j');
        else Keyboard.press('j');
        if (digitalRead(KEY_X) && digitalRead(KEY_Y)) Keyboard.release('k');
        else Keyboard.press('k');
        if (digitalRead(KEY_L)) Keyboard.release('`');
        else Keyboard.press('`');
        if (digitalRead(KEY_R)) Keyboard.release(KEY_ESC);
        else Keyboard.press(KEY_ESC);
    } else {
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
        if (digitalRead(KEY_L)) Keyboard.release('c');
        else Keyboard.press('c');
        if (digitalRead(KEY_R)) Keyboard.release('d');
        else Keyboard.press('d');
    }
}
