#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial ser(12, 13); //RX, TX
#include "PCA9685.h"
PCA9685 driver;
PCA9685_ServoEvaluator pwmServo(102, 470);

int angles[5] = {0, 0, 0, 0, 0};
int pomp = 3;

int param (String in, int side) { //work
  int param = side == 1 ? ( split(split(in, '(', 1), ',', 0).toInt()) : (split(split(split(split(in, '(', 1), ',', 1), ')', 0), ' ', 1).toInt());
  return param;
}


void setAngle_(int servo_id, int angle) {
  driver.setChannelPWM(servo_id, pwmServo.pwmForAngle(angle));
}

void setAngle(int servo_id, int angle, int del) {
  if (del == 0) {
    setAngle_(servo_id, angle);
    angles[servo_id] = angle;
    return;
  }

  int prev = angles[servo_id];
  int curr = angle;

  if (prev < curr) {
    for (int a = prev; a <= curr; ++a) {
      setAngle_(servo_id, a);
      delay(del);
    }
  } else {
    for (int a = prev; a > curr; --a) {
      setAngle_(servo_id, a);
      delay(del);
    }
  }

  angles[servo_id] = curr;
}
void setAngle(int servo_id, int angle) {
  setAngle(servo_id, -angle, 0);
  angles[servo_id] = angle;
}

void test (){
 smeh();
}

void straight() {
  setAngle(0, 0);
  for (int i = 1; i < 5; ++i) {
    setAngle(i, 10);
    delay(10);
  }
}

void enablePomp() { //work
  digitalWrite(pomp, LOW);
}

void disablePomp() {  //work
  digitalWrite(pomp, HIGH);
}

void ostrich() {  // спрятал голову в песок work
  setAngle(1, 75);
  setAngle(2, -80);
  setAngle(3, -78);
  delay(1000);
  setAngle(0, 80);
}

void smeh () {   //work
  setAngle(0, 0);
  delay(500);
  setAngle(3, 60);
  delay(500);
  setAngle(4, -90);
  delay(500);
  setAngle(2, 90);
  delay(500);
  setAngle(1, -35);
  delay(500);
  setAngle(4, -70);
  delay(500);
}


void grab(int angle, double distance, double height) {
  setAngle(0, angle, 10);

  delay(400);

  double a1 = 30 + 50 * distance;
  double a2 =  0 + 50 * (1 - distance);
  double a4 = 20 + 38 * distance;

  a1 -= 10 * height;
  a4 += 10 * height;

  setAngle(4, 20);
  delay(100);
  setAngle(1, a1);
  setAngle(2, a2);
  setAngle(3, a2);
}

void grab() {
//  setAngle(0, 0);
//  setAngle(1, 80);
//  setAngle(3, 40);
  enablePomp();
  grab(0, 0.25, 0.9);
  delay(4000);
  straight();
}

void midPos() {
  setAngle(1, 60);
  setAngle(2, -40);
  setAngle(3, -85);
  setAngle(4, -10);
}

void takeUp() {
  setAngle(1, 35);
  setAngle(1, 0);
  setAngle(3, -45);
}

void takeDown() {
  setAngle(1, 35);
  setAngle(2, -80);
  setAngle(3, -60);
  setAngle(4, -20);
}

void kickRight() {
  disablePomp();
  setAngle(0, 20);
  delay(1000);
}

void kickLeft() {
  disablePomp();
  delay(300);
  setAngle(0, -20);
  delay(1000);
}

void zero() {
  disablePomp();
  setAngle(1, 45);
  setAngle(4, 10);
  ostrich();
}



void takeLU() {
  grab();
  midPos();
  delay(1000);
  setAngle(0, 20);
  takeUp();
  delay(1000);
  kickLeft();
  zero();
}

void takeRU() {
  grab();
  midPos();
  delay(1000);
  setAngle(0, -25);
  takeUp();
  delay(1000);
  kickRight();
  zero();
}

void takeLD() {
  grab();
  midPos();
  delay(1000);
  setAngle(0, 23);
  takeDown();
  delay(300);
  kickLeft();
  zero();
}

void takeRD() {
  enablePomp();
  grab();
  midPos();
  delay(1000);
  setAngle(0, -35);
  takeDown();
  delay(300);
  delay(300);
  kickRight();
  zero();
}

int takeNumber = 0;
void take() {
  switch (takeNumber) {
    case 3:
      takeRU();
      break;
    case 1:
      takeLU();
      break;
    case 2:
      takeLD();
      break;
    case 0:
      takeRD();
      break;
  }
  takeNumber++;
} 

String split(String StringToSplit, char SplitChar, int StringPartIndex) {
  StringToSplit += SplitChar;
  String originallyString = StringToSplit;
  String outString = "";
  for (int i1 = 0; i1 <= StringPartIndex; i1++)
  {
    outString = "";
    int SplitIndex = StringToSplit.indexOf(SplitChar);

    if (SplitIndex == -1)
    {
      return outString;
    }
    for (int i2 = 0; i2 < SplitIndex; i2++)
    {
      outString += StringToSplit.charAt(i2);
    }
    StringToSplit = StringToSplit.substring(StringToSplit.indexOf(SplitChar) + 1);
  }
  return outString;
}
void setup() {
  ser.begin(9600);
  Wire.begin();
  Wire.setClock(400000);
  driver.resetDevices();
  driver.init(B000000);
  driver.setPWMFrequency(50);
  pinMode(pomp, OUTPUT);
  disablePomp();
  ostrich();
  smeh();
}

void loop() {
//  while (Serial.available() > 0) {  // ждём команду
//    String in = String(Serial.readStringUntil('\n'));  // считывание строки
//    if (in != "") {
//      Serial.println(in);
//      String cmd = split(in, '(', 0);  // находим имя команды
//
//      if ({
//        Serial.print(cmd);
//        Serial.print(REC);
//        delay(100);
//        Serial.print(ERR);
//      }
//    }
//  }
}
