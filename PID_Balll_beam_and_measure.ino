#include <Servo.h>
#include "pins.h"
#include "lcd_and_button.h"

Servo myServo;
HMI myHMI;

float val, distance;
int flag = 4, period = 50, x5, x4, x3, x2, x1;
float elapsedTime, time, timePrev;        //Variables for time control
float distance_previous_error, distance_error, pre_PID;
float input;

float kp = 2.0; //Mine was 8 2- for micro; 5 for normal
float ki = 0.2; //Mine was 0.2
float kd = 80.0; //Mine was 3100
float distance_setpoint = 22.0;           //Should be the distance from sensor to the middle of the bar in mm
float PID_p, PID_i, PID_d, PID_total;

void greeting();
void measure();
float get_dist();

void setup() {
  // put your setup code here, to run once:
  pinMode(A1, INPUT);
//   pinMode(Button, INPUT_PULLUP);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  myServo.attach(SERVO_PIN);
  Serial.begin(9600);
  attachInterrupt(0, measure, FALLING);
  time = millis();
  greeting();
  myHMI.HMIinit(&kp, &ki, &kd, &distance_setpoint);
}

void loop() {
  // put your main code here, to run repeatedly:
  myHMI.run();
//   if (Serial.available() > 0) {
//     flag = Serial.parseInt();
//     Serial.flush();
//   }
//   /* MEASURING MODE */
//   if (flag == 1) {
// //    for (int i=0; i<100; i++){
// //      distance = get_dist();
// //      Serial.println(distance, 4);
// //    }
//     distance = get_dist();
//     Serial.println(distance, 4);
// //    Serial.print("Third order: ");
// //    Serial.print(8.50089190269773 * pow(distance, 4) - 67.8617420925319 * pow(distance, 3) + 203.442157016196 * pow(distance, 2) - 279.701493381125 * distance + 166.440378686084);
// //    Serial.print("\t Linear: ");
// //    Serial.println((37.623762145518 * (1 / distance) - 5.97506167709363), 6);
//   }
//   delay(100);
//   /* TEST MOTOR MODE 2 */
//   if (flag == 2) {
//     Serial.println("Servo mode!");
//     while (1) {
//       if (Serial.available() > 0) {
//         input = Serial.parseInt();
//         if (input >= 0 && input <= 180) {
//           myServo.write(input);
//         }
//         else myServo.writeMicroseconds(input);
//         Serial.flush();
//         Serial.println(input);
//         if (input == 1) {
//           Serial.println("End servo mode!");
//           myServo.write(90);
//           flag = 0;
//           break;
//         }
//       }
//     }
//   }
//   /* PID Ball beam mode */
//   if (flag == 3) {
    Serial.println("Ball beam micro mode!");
    if (millis() > time + period) {
        time = millis();
        x4 = x3;
        x3 = x2;
        x2 = x1;
        x1 = distance;
        distance = get_dist();
        distance = 8.50089190269773 * pow(distance, 4) - 67.8617420925319 * pow(distance, 3) + 203.442157016196 * pow(distance, 2) - 279.701493381125 * distance + 166.440378686084;
        distance = (x4+x3+x2+x1+distance)/5;
        distance_error = distance_setpoint - distance;
        PID_p = kp * distance_error;
        PID_d = kd * ((distance_error - distance_previous_error) / period);

        if (-3 < distance_error && distance_error < 3)
        {
            PID_i = PID_i + (ki * distance_error);
        }
        else
        {
            PID_i = 0;
        }
        PID_total = PID_p + PID_i + PID_d;
        PID_total = map(PID_total, -150, 150, 180, 0);
        PID_total = map(PID_total, 180, 0, 3000, 500);
        PID_total = PID_total - 280;
        //        Serial.print(PID_total);
        Serial.println(distance);
    //        Serial.print("\t");
    //        Serial.println(distance_setpoint);
        if (PID_total < 700) {
            PID_total = 700;
        }
        if (PID_total > 1850) {
            PID_total = 1850;
        }

        myServo.writeMicroseconds(PID_total);
        distance_previous_error = distance_error;
        pre_PID = PID_total;
    }
    // }
//   }
//   if (flag == 4) {
//     Serial.println("Ball beam mode!");
//     while (1) {
//       if (Serial.available() > 0) {
//         input = Serial.parseFloat();
//         Serial.println(input);
//         if (input == 1) {
//           Serial.println("End Ball beam mode!");
//           myServo.write(90);
//           flag = 0;
//           break;
//         }
//         else kp = input;
//       }

//       if (millis() > time + period) {
//         time = millis();
//         distance = get_dist();
//         distance = 8.50089190269773 * pow(distance, 4) - 67.8617420925319 * pow(distance, 3) + 203.442157016196 * pow(distance, 2) - 279.701493381125 * distance + 166.440378686084;
//         distance_error = distance_setpoint - distance;
//         PID_p = kp * distance_error;
//         PID_d = kd * ((distance_error - distance_previous_error) / period);

//         if (-3 < distance_error && distance_error < 3)
//         {
//           PID_i = PID_i + (ki * distance_error);
//         }
//         else
//         {
//           PID_i = 0;
//         }
//         PID_total = PID_p + PID_i + PID_d;
//         PID_total = map(PID_total, -150, 150, 180, 0);
//         //        Serial.print(kp);
// //        Serial.print("\t");
//         Serial.print(distance);
//         Serial.print("\t");
//         Serial.println(distance_setpoint);
//         if (PID_total < 30) {
//           PID_total = 30;
//         }
//         if (PID_total > 135) {
//           PID_total = 135;
//         }

//         myServo.write(PID_total);
//         distance_previous_error = distance_error;
//         pre_PID = PID_total;
//       }
//     }
//   }
}

void greeting() {

}
void measure() {
  flag = 3;
}

float get_dist() {
  int count = 0;
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
  digitalWrite(LED_RED_PIN, LOW);
  int here_count = count;
  avg = avg / count;
  threshold = avg + (avg - min_val);
  while (count <= here_count + 100) {
    val = analogRead(A1) * 0.0048828125;
    digitalWrite(LED_GREEN_PIN, HIGH);
    if (val <= threshold) {
      count++;
      nice_avg += val;
    }
  }
  nice_avg = nice_avg / (count - here_count);
  digitalWrite(LED_GREEN_PIN, LOW);
  flag = 0;
  return nice_avg;
}
