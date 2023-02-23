#include "lcd_and_button.h"
#include "pins.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int btn_state;
int enc_btn_state;
int enc_btn_state_prev = 1, btn_state_prev = 1;
int menu_select = 0, inc_select = 0;

float increment[4] = {0.01, 0.1, 1, 10};

int currentStateA, lastStateA; 

byte Arrow[8] = {
0b00000,
0b00000,
0b10000,
0b11000,
0b11100,
0b11000,
0b10000,
0b00000
};
byte TwoWayArrow[8] = {
0b00100,
0b01110,
0b11111,
0b00000,
0b00000,
0b11111,
0b01110,
0b00100
};

HMI::HMI() {
    this->enc_pin_a = ENCODER_PIN_A;
    this->enc_pin_b = ENCODER_PIN_B;
    this->enc_pin_sw = ENCODER_PIN_SWITCH;
    this->button_pin = MENU_BUTTON_PIN;
}

void HMI::HMIinit(float *kp, float *ki, float *kd, float *distance_setpoint) {
    this->p[0] = kp;
    this->p[1] = ki;
    this->p[2] = kd;
    this->p[3] = distance_setpoint;

    lcd.init();
    lcd.backlight();
    lcd.createChar(0, Arrow);
    lcd.createChar(1, TwoWayArrow);
    lcd.setCursor(1,0);
    lcd.print("Ki");
    lcd.setCursor(5,0);
    lcd.print("Kp");
    lcd.setCursor(9,0);
    lcd.print("Kd");
    lcd.setCursor(13,0);
    lcd.print("Set");
    lcd.setCursor(10, 1);
    lcd.write(byte(1));
    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    lcd.setCursor(12, 1);
    lcd.print(increment[0]);
    pinMode(enc_pin_a, INPUT);
    pinMode(enc_pin_b, INPUT);
    pinMode(button_pin, INPUT_PULLUP);
    pinMode(enc_pin_sw, INPUT); 
}

void HMI::run() {   
    enc_btn_state = digitalRead(enc_pin_sw); 
    if (enc_btn_state == 0 && enc_btn_state_prev == 1)
    {
        if (inc_select >= 3)
            {
                inc_select = 0;  
            }
        else
            {
                inc_select++;  
            } 
        updateParameters(menu_select, btn_state, increment[inc_select]); 
    }
    enc_btn_state_prev = enc_btn_state;

    btn_state = digitalRead(button_pin);
    if (btn_state == 0 && btn_state_prev == 1)
    {
        inc_select = 0;
        if (menu_select >= 3)
            { 
                menu_select = 0;  
            }
        else
            {
                menu_select++;  
            } 
        updateParameters(menu_select, btn_state, increment[inc_select]);
        lcd.setCursor(0, 1);
        lcd.print("          ");
        lcd.setCursor(0, 1);
        lcd.print(*p[menu_select]);
    }
    btn_state_prev = btn_state;

    encoderState(p[menu_select], increment[inc_select]);
}

void HMI::updateParameters(int gtmenu, int gttang, float inc) 
{
    if (gtmenu != 0) {
        lcd.setCursor(gtmenu*4, 0);
        lcd.write(byte(0));
        lcd.setCursor((gtmenu-1)*4, 0);
        lcd.print(" ");
    }
    else {
        lcd.setCursor(gtmenu, 0);
        lcd.write(byte(0));
        lcd.setCursor(12, 0);
        lcd.print(" ");
    }
    lcd.setCursor(12, 1);
    lcd.print("    ");
    lcd.setCursor(12, 1);
    lcd.print(inc);
}

void HMI::encoderState(float *p, float gttang)
{
    currentStateA = digitalRead(enc_pin_a);
    if (currentStateA != lastStateA  && currentStateA == 1)
    {
      if (digitalRead(enc_pin_b) != currentStateA) 
      {
        *p -= gttang;
      } 
      else 
      {
        *p += gttang;
      }
      if (*p <0) {
        *p = 0; 
      }
      lcd.setCursor(0, 1);
      lcd.print("          ");
      lcd.setCursor(0, 1);
      lcd.print(*p);
    }
    lastStateA = currentStateA;
}
