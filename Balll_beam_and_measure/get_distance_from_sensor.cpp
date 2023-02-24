#include "get_distance_from_sensor.h"

int count = 0;
float nice_avg = 0, avg = 0;
float threshold = 0, min_val = 99999;
float val;
int here_count;
float distance_cm;

float get_distance_cm() {
    digitalWrite(LED_GREEN_PIN, HIGH);
    while (count < 100) {
        count++;
        val = analogRead(SENSOR_PIN) * 0.0048828125;
        avg += val;
        if (min_val > val) {
            min_val = val;
        }
    }
    digitalWrite(LED_RED_PIN, LOW);
    here_count = count;
    avg = avg / count;
    threshold = avg + (avg - min_val);
    while (count <= here_count + 100) {
        val = analogRead(SENSOR_PIN) * 0.0048828125;
        digitalWrite(LED_GREEN_PIN, HIGH);
        if (val <= threshold) {
        count++;
        nice_avg += val;
        }
    }
    nice_avg = nice_avg / (count - here_count);
    digitalWrite(LED_GREEN_PIN, LOW);

    distance_cm = 8.50089190269773 * pow(nice_avg, 4) - 67.8617420925319 * pow(nice_avg, 3) + 203.442157016196 * pow(nice_avg, 2) - 279.701493381125 * nice_avg + 166.440378686084;

    return distance_cm;
}