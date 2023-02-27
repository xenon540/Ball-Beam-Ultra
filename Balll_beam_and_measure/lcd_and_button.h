#ifndef LCD_AND_BUTTON_H
#define LCD_AND_BUTTON_H

#include <Arduino.h>

extern float sys_var[];
extern float increment[];
extern int check;

class HMI {
private:
    byte enc_pin_sw; 
    byte button_pin;
public:
    HMI();
    void HMIinit();
    int run();
    void updateParameters(int gtmenu, float inc);
};
#endif