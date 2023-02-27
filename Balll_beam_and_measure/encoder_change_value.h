#ifndef ENCODER_CHANGE_VALUE_H
#define ENCODER_CHANGE_VALUE_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

extern float sys_var[4]; 
extern int menu_select, inc_select;
extern LiquidCrystal_I2C lcd;
extern int operation_mode;

void encoderChange();

#endif