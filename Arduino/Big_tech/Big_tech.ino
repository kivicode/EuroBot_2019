#include <Wire.h>
#include "PCA9685.h"

PCA9685 driver;
PCA9685_ServoEvaluator pwmServo(102, 470);


int angles[5] = {0, 0, 0, 0, 0};

void setAngle(int servo_id, int angle) {
  driver.setChannelPWM(servo_id, pwmServo.pwmForAngle(angle));
}

int sound = 51;
int pomp = 44;

int A_open = 45;
int A_close = 46;

int B_close = 48;
int B_open = 50;

int C_close = 47;
int C_open = 49;

const int start = 0;
const int take = 1;

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  driver.resetDevices();
  driver.init(B000000);
  driver.setPWMFrequency(50);
  Serial.begin(9600);
  Serial1.begin(9600);


  levelDown();
  pompsMid();
  //  setAngle(3, 3);
  //  setAngle(4, -40);
  //
  for (int i = 40; i <= 51; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  digitalWrite(A_close, LOW);
  digitalWrite(B_close, LOW);
  digitalWrite(C_close, LOW);
}


void levelUp() {
  setAngle(0, -57);
  setAngle(2, 64);
  setAngle(5, 90);
}

void levelDown() {
  setAngle(0, 67);
  setAngle(2, -65);
  setAngle(5, -40);
}


void pompsMid() {
  setAngle(7, 55);
  setAngle(3, 3);
  setAngle(4, -40);
}

void pompsDown() {
  setAngle(7, -50);
  setAngle(3, 90);
  setAngle(4, 50);
}
void loop() {
  int data = Serial1.read();
  if (data != -1) {
    switch (data) {
      case 2:
        levelDown();
        pompsMid();
        digitalWrite(C_close, LOW);
        digitalWrite(C_open, HIGH);
        digitalWrite(A_open, LOW);
        digitalWrite(B_open, LOW);
        digitalWrite(A_close, HIGH);
        digitalWrite(B_close, HIGH);
        digitalWrite(pomp, LOW);
        delay(1000);
        pompsDown();
        delay(1000);
        digitalWrite(C_close, HIGH);
        digitalWrite(pomp, HIGH);
        digitalWrite(A_open, HIGH);
        digitalWrite(B_open, HIGH);

        digitalWrite(A_close, LOW);
        digitalWrite(B_close, LOW);

        break;

      case 1:
        digitalWrite(pomp, LOW);
        digitalWrite(A_close, LOW);
        digitalWrite(B_close, LOW);
        digitalWrite(C_open, LOW);
        Serial1.write(1);
        break;
    }
  }
}
