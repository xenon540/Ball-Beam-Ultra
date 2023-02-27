#include "lcd_and_button.h"
#include "pins.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int btn_state, enc_btn_state;
int mode;
int enc_btn_state_prev = 1, btn_state_prev = 1;
int menu_select = 0, inc_select = 0;


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
    this->enc_pin_sw = ENCODER_PIN_SWITCH;
    this->button_pin = MENU_BUTTON_PIN;
}

void HMI::HMIinit() {
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, Arrow);
    lcd.createChar(1, TwoWayArrow);
    lcd.setCursor(1,0);
    lcd.print("Kp");
    lcd.setCursor(5,0);
    lcd.print("Ki");
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
}

int HMI::run() {   
    if (check == 1) {
        check = 0;
        lcd.setCursor(0, 1);
        lcd.print("          ");
        lcd.setCursor(0, 1);
        lcd.print(sys_var[menu_select]);
    } //* Only update if the ISR is called, make the program run less slowly
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
        updateParameters(menu_select, increment[inc_select]); 
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
        updateParameters(menu_select, increment[inc_select]);
        lcd.setCursor(0, 1);
        lcd.print("          ");
        lcd.setCursor(0, 1);
        lcd.print(sys_var[menu_select]);
    }
    btn_state_prev = btn_state;

    /* Check if two button is both pressed, used to choose other mode,.. !? */ 
    if (btn_state == 0 && enc_btn_state == 0) {
        mode += 1;
        if (mode > 2) {
            mode = 0;
        }
    }
    return mode;
}

void HMI::updateParameters(int gtmenu, float inc) 
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