#include <Wire.h>
#include "PCA9685.h"

PCA9685 driver;
PCA9685_ServoEvaluator pwmServo(102, 470);

void setAngle(int servo_id, int angle) {
  if (servo_id == B_level) {
    angle -= 40;
  }
  driver.setChannelPWM(servo_id, pwmServo.pwmForAngle(servo_id != C_level ? angle : angle - 20));
}

void levelDown() {
  setAngle(A_level, -30);
  setAngle(B_level, -20);
  setAngle(C_level, 50);
}

void levelUp() {
  setAngle(A_level, 67);
  setAngle(B_level, 65);
  setAngle(C_level, -40);
}


void pompsMid() {
  setAngle(A_pomp, -42);
  setAngle(B_pomp, 0);
  setAngle(C_pomp, 55);
}

void pompsDown() {
  setAngle(A_pomp, 40);
  setAngle(B_pomp, 90);
  setAngle(C_pomp, -30);
}

void enablePomp() {
  digitalWrite(pomp, LOW);
}

void disablePomp() {
  digitalWrite(pomp, HIGH);
}

void grabA() {
  setAngle(A_pomp, -42);
  digitalWrite(A_grab, LOW);
  digitalWrite(A_kick, HIGH);
}

void grabB() {
  setAngle(B_pomp, 0);
  digitalWrite(B_grab, LOW);
  digitalWrite(B_kick, HIGH);
}

void grabC() {
  setAngle(C_pomp, 55);
  digitalWrite(C_grab, LOW);
  digitalWrite(C_kick, HIGH);
}



void kickA() {
  setAngle(A_pomp, 30);
  digitalWrite(A_grab, HIGH);
  digitalWrite(A_kick, LOW);
}

void kickB() {
  setAngle(B_pomp, 90);
  digitalWrite(B_grab, HIGH);
  digitalWrite(B_kick, LOW);
}

void kickC() {
  setAngle(C_pomp, -40);
  digitalWrite(C_grab, HIGH);
  digitalWrite(C_kick, LOW);
}
