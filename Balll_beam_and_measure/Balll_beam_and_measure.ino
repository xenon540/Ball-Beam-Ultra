#include <Servo.h>
#include "pins.h"
#include "lcd_and_button.h"
#include "encoder_change_value.h"
#include "get_distance_from_sensor.h"
#include "PID_controller.h"

Servo myServo;
HMI myHMI;

int both_click, flag;
float distance;
int pid_period = 50;
float elapsedTime, time, timePrev;        //Variables for time control

// float sys_var[4] = {2.0, 0.2, 80.0, 22.0}; // Kp, Ki, Kd, Set_p 

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
    both_click = myHMI.run();
    if (both_click == 1) {
        flag = !(flag); //Toggle the flag 
    }
    if (flag == 1) {
        // myServo.write(middle_angle???)
        // measuring();
    }

    distance = get_distance_cm();
    myServo.write(servoAngle(distance));

}

void greeting() {
    /* Do something cool when power-on */ 
}