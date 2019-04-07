#include <SoftwareSerial.h>
#include <Wire.h>
#include "PCA9685.h"

#define YELLOW 1
#define PURPLE -1

PCA9685 driver;
PCA9685_ServoEvaluator pwmServo(102, 470);

#define SIDE PURPLE

const int take = 1;

SoftwareSerial ser(A2, A1); //RX, TX

void setup() {
  Serial.begin(9600);
  ser.begin(9600);
  initPins();
  diagRF(910);

  right(87);
  rotateL(9);
  forward(120);
  rotateL(10);
  forward(70);
  ser.write(2);
  delay(300);
  backward(100);
}
int p = 13;
void loop() {
}
