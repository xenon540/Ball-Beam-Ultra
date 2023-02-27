#include "get_distance_from_sensor.h"

int count = 0;
float nice_avg = 0, avg = 0;
float threshold = 0, min_val = 99999;
float val;
int here_count;
float distance_cm;

float get_distance_cm() {
    nice_avg = analogRead(SENSOR_PIN) * 0.0048828125;
    distance_cm = 8.50089190269773 * pow(nice_avg, 4) - 67.8617420925319 * pow(nice_avg, 3) + 203.442157016196 * pow(nice_avg, 2) - 279.701493381125 * nice_avg + 166.440378686084;
    return distance_cm;
}