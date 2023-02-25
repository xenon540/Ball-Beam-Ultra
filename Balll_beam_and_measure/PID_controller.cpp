#include "PID_controller.h"

float sys_var[4] = {2.0, 0.2, 80.0, 22.0}; // Kp, Ki, Kd, Set_p 
float PID_p, PID_i, PID_d, PID_total;
float previous_distance_error = 0;

float servoAngle(float current_point) {
    float distance_error =  sys_var[3] - current_point; 
    PID_p = sys_var[0] * distance_error;
    PID_d = sys_var[2] * ((distance_error - previous_distance_error) / PID_period);
    if (-3 < distance_error && distance_error < 3) {
        PID_i = PID_i + (sys_var[1] * distance_error);
    }
    else {
        PID_i = 0;
    }
    PID_total = PID_p + PID_i + PID_d;
    PID_total = map(PID_total, -150, 150, 180, 0);
    previous_distance_error = distance_error;
    return previous_distance_error;
}