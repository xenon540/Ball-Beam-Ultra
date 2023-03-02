#include "measuring_mode.h"
#include "pins.h"

void measuring() {
    while (1) {
        if (digitalRead(MENU_BUTTON_PIN) && !digitalRead(ENCODER_PIN_SWITCH)) {
            break;
        }
        if (digitalRead(MENU_BUTTON_PIN)) {
            int count = 0;
            float val;
            float nice_avg = 0, avg = 0;
            float threshold = 0, min_val = 99999;
            digitalWrite(LED_RED_PIN, HIGH);
            while (count < 100) {
                count++;
                val = analogRead(A1) * 0.0048828125;
                avg += val;
                if (min_val > val) {
                    min_val = val;
                }
            }
            int here_count = count;
            avg = avg / count;
            threshold = avg + (avg - min_val);
            while (count <= here_count + 100) {
                val = analogRead(A1) * 0.0048828125;
                if (val <= threshold) {
                    count++;
                    nice_avg += val;
                }
            }
            nice_avg = nice_avg / (count - here_count);
            // delay(1000);
            digitalWrite(LED_RED_PIN, LOW);
            Serial.println(nice_avg, 8);
        }
    }
    delay(1000);
}