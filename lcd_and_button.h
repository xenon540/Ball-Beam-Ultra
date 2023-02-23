#ifndef LCD_AND_BUTTON_H
#define LCD_AND_BUTTON_H

#include <Arduino.h>

class HMI {
private:
    byte enc_pin_a;
    byte enc_pin_b;
    byte enc_pin_sw; 
    byte button_pin;
    float *p[4];

public:
    HMI();
    void HMIinit(float *kp, float *ki, float *kd, float *distance_setpoint);
    void run();
    void updateParameters(int gtmenu, int gttang, float inc);
    void encoderState(float *p, float gttang);
};
#endif