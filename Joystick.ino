#include "Keyboard.h"

#define KEY_UP      2
#define KEY_LEFT    3
#define KEY_DOWN    4
#define KEY_RIGHT   5
#define KEY_FL      6
#define KEY_A       A3
#define KEY_B       A0
#define KEY_X       A2
#define KEY_Y       A1
#define KEY_FR      15

void setup() {
    /*INPUT Mode*/
    pinMode(KEY_UP, INPUT);
    pinMode(KEY_LEFT, INPUT);
    pinMode(KEY_DOWN, INPUT);
    pinMode(KEY_RIGHT, INPUT);
    pinMode(KEY_FL, INPUT);
    pinMode(KEY_A, INPUT);
    pinMode(KEY_B, INPUT);
    pinMode(KEY_X, INPUT);
    pinMode(KEY_Y, INPUT);
    pinMode(KEY_FR, INPUT);
    /*PULL UP*/
    digitalWrite(KEY_UP, HIGH);
    digitalWrite(KEY_LEFT, HIGH);
    digitalWrite(KEY_DOWN, HIGH);
    digitalWrite(KEY_RIGHT, HIGH);
    digitalWrite(KEY_FL, HIGH);
    digitalWrite(KEY_A, HIGH);
    digitalWrite(KEY_B, HIGH);
    digitalWrite(KEY_X, HIGH);
    digitalWrite(KEY_Y, HIGH);
    digitalWrite(KEY_FR, HIGH);
    
    Keyboard.begin();
}

void loop() {
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
    if (digitalRead(KEY_FL)) Keyboard.release('c');
    else Keyboard.press('c');
    if (digitalRead(KEY_FR)) Keyboard.release('d');
    else Keyboard.press('d');
}
