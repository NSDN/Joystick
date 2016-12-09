#include "Keyboard.h"

#define KEY_LUP      6
#define KEY_LLEFT    8
#define KEY_LRIGHT   9
#define KEY_L1       5
#define KEY_L2       7

#define KEY_RUP      15
#define KEY_RLEFT    10
#define KEY_RRIGHT   16
#define KEY_R1       14
#define KEY_R2       A0

#define MODE_A       0
#define MODE_B       1

void setup() {
    /*INPUT Mode*/
    pinMode(KEY_LUP, INPUT);
    pinMode(KEY_LLEFT, INPUT);
    pinMode(KEY_LRIGHT, INPUT);
    pinMode(KEY_L1, INPUT);
    pinMode(KEY_L2, INPUT);
    
    pinMode(KEY_RUP, INPUT);
    pinMode(KEY_RLEFT, INPUT);
    pinMode(KEY_RRIGHT, INPUT);
    pinMode(KEY_R1, INPUT);
    pinMode(KEY_R2, INPUT);

    pinMode(MODE_A, INPUT);
    pinMode(MODE_B, INPUT);
    
    /*PULL UP*/
    digitalWrite(KEY_LUP, HIGH);
    digitalWrite(KEY_LLEFT, HIGH);
    digitalWrite(KEY_LRIGHT, HIGH);
    digitalWrite(KEY_L1, HIGH);
    digitalWrite(KEY_L2, HIGH);
    
    digitalWrite(KEY_RUP, HIGH);
    digitalWrite(KEY_RLEFT, HIGH);
    digitalWrite(KEY_RRIGHT, HIGH);
    digitalWrite(KEY_R1, HIGH);
    digitalWrite(KEY_R2, HIGH);

    digitalWrite(MODE_A, HIGH);
    digitalWrite(MODE_B, HIGH);

    delay(1000);
    
    Keyboard.begin();
}

void loop() {
    if (!digitalRead(MODE_A) && digitalRead(MODE_B)) {

        if (digitalRead(KEY_L1)) Keyboard.release('s');
        else Keyboard.press('s');
        if (digitalRead(KEY_LUP)) Keyboard.release('d');
        else Keyboard.press('d');  
        if (digitalRead(KEY_L2)) Keyboard.release('f');
        else Keyboard.press('f');
        if (digitalRead(KEY_R1)) Keyboard.release('j');
        else Keyboard.press('j');
        if (digitalRead(KEY_RUP)) Keyboard.release('k');
        else Keyboard.press('k');
        if (digitalRead(KEY_R2)) Keyboard.release('l');
        else Keyboard.press('l');
        
        if (digitalRead(KEY_LRIGHT) || digitalRead(KEY_RLEFT)) Keyboard.release(KEY_ESC);
        else Keyboard.press(KEY_ESC);
        if (digitalRead(KEY_LLEFT) || digitalRead(KEY_RRIGHT)) Keyboard.release('`');
        else Keyboard.press('`');
        
    } else if (!digitalRead(MODE_B) && digitalRead(MODE_A)) {
        
        if (digitalRead(KEY_RUP)) Keyboard.release(KEY_UP_ARROW);
        else Keyboard.press(KEY_UP_ARROW);
        if (digitalRead(KEY_RLEFT)) Keyboard.release(KEY_LEFT_ARROW);
        else Keyboard.press(KEY_LEFT_ARROW);  
        if (digitalRead(KEY_RRIGHT)) Keyboard.release(KEY_RIGHT_ARROW);
        else Keyboard.press(KEY_RIGHT_ARROW);
        if (digitalRead(KEY_LUP)) Keyboard.release(KEY_DOWN_ARROW);
        else Keyboard.press(KEY_DOWN_ARROW);
        if (digitalRead(KEY_R1) || digitalRead(KEY_R2)) Keyboard.release(' ');
        else Keyboard.press(' ');

        if (digitalRead(KEY_L1)) Keyboard.release(KEY_ESC);
        else Keyboard.press(KEY_ESC);
        if (digitalRead(KEY_L2)) Keyboard.release(KEY_RETURN);
        else Keyboard.press(KEY_RETURN);

        if (digitalRead(KEY_LLEFT)) Keyboard.release('z');
        else Keyboard.press('z');
        if (digitalRead(KEY_LRIGHT)) Keyboard.release('x');
        else Keyboard.press('x');

    } else if (!digitalRead(MODE_B) && !digitalRead(MODE_A)) {
  
        
        
    } else {
        
        
        
    }
}
