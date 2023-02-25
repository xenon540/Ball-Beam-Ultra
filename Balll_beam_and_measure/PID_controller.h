#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <Arduino.h>

// extern Serial;
extern int PID_period;

float servoAngle(float current_point);

#endif