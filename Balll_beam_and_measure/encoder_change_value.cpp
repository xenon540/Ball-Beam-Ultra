#include "encoder_change_value.h"
#include "pins.h"

float increment[4] = {0.01, 0.1, 1, 10};
int check = 0;

void encoderChange() {
    if (digitalRead(ENCODER_PIN_B) != 1) {
        sys_var[menu_select] += increment[inc_select];
    } 
    else {
        sys_var[menu_select] -= increment[inc_select];
        if (sys_var[menu_select] <0) {
            sys_var[menu_select] = 0; 
        }
    }
    check = 1;
}