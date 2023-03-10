#include <Servo.h>
#include "pins.h"
#include "lcd_and_button.h"
#include "encoder_change_value.h"
#include "get_distance_from_sensor.h"
#include "PID_controller.h"
#include "measuring_mode.h"

Servo myServo;
HMI myHMI;

int both_click, operation_mode, operation_mode_prev;
float distance;
int pid_period = 50;
float elapsedTime, time, timePrev;        //Variables for time control

void greeting();

void setup() {
    // put your setup code here, to run once:
    pinMode(SENSOR_PIN, INPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(ENCODER_PIN_A, INPUT);
    pinMode(ENCODER_PIN_B, INPUT);
    pinMode(MENU_BUTTON_PIN, INPUT_PULLUP);
    pinMode(ENCODER_PIN_SWITCH, INPUT); 
    myServo.attach(SERVO_PIN);
    Serial.begin(9600);
    attachInterrupt(0, encoderChange, FALLING);
    greeting();
    myHMI.HMIinit();
    time = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
    operation_mode = myHMI.run();
    if (operation_mode) {
        lcd.setCursor(0, 1);
        lcd.print("          ");
        lcd.setCursor(0, 1);
        lcd.print("Measuring!");
        measuring();
        lcd.setCursor(0, 1);
        lcd.print("          ");
        delay(1000);
    }
    distance = get_distance_cm();
    Serial.print(operation_mode);
    myServo.write(servoAngle(distance));

}

void greeting() {
    /* Do something cool when power-on */ 
}