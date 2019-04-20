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

int starter = 11;
int switcher = 10;

const int start = 0;
const int take = 1;

void setup() {
  //  Wire.begin();
  //  Wire.setClock(400000);
  //  driver.resetDevices();
  //  driver.init(B000000);
  //  driver.setPWMFrequency(50);
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  pinMode(starter, INPUT_PULLUP);
  pinMode(switcher, INPUT_PULLUP);
  for (int i = 40; i <= 51; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  pinMode(12, OUTPUT);

  //  while (digitalRead(starter) != 0) {}
  //
  //  Serial1.write(digitalRead(switcher));

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

long int last_time = millis();
bool started = false;
void loop() {

  while (Serial3.available() > 0) {
    int data = Serial3.read();
    if (data != 0 && started) {
      Serial.println("Stop");
      last_time = millis();
      started = false;
    } else if (millis() - last_time > 2000 && !started) {
      Serial.println("Start");
      started = true;
    }
  }

  //  int data = Serial2.read();
  //  if (data == 1) {
  //    levelDown();
  //    pompsMid();
  //    setAngle(4, 50);
  //    digitalWrite(A_close, LOW);
  //    digitalWrite(A_open, HIGH);
  //    digitalWrite(C_open, LOW);
  //    digitalWrite(B_open, LOW);
  //    digitalWrite(C_close, HIGH);
  //    digitalWrite(B_close, HIGH);
  //    digitalWrite(pomp, LOW);
  //    delay(2000);
  //    pompsDown();
  //    delay(1000);
  //    digitalWrite(C_close, HIGH);
  //    digitalWrite(pomp, HIGH);
  //    digitalWrite(A_open, HIGH);
  //    digitalWrite(B_open, HIGH);
  //
  //    digitalWrite(C_close, LOW);
  //    digitalWrite(B_close, LOW);
  //    delay(400);
  //    digitalWrite(C_close, HIGH);
  //    digitalWrite(B_close, HIGH);
  //    pompsMid();
  //    setAngle(4, 50);
  //  } else if (data == 2) {
  //    //        Serial.println(2);
  //    levelDown();
  //    pompsMid();
  //    setAngle(4, 50);
  //    digitalWrite(A_close, LOW);
  //    digitalWrite(A_open, HIGH);
  //    digitalWrite(C_open, LOW);
  //    digitalWrite(B_open, LOW);
  //    digitalWrite(C_close, HIGH);
  //    digitalWrite(B_close, HIGH);
  //    digitalWrite(pomp, LOW);
  //    delay(2000);
  //    levelUp();
  //    pompsDown();
  //    delay(1000);
  //    digitalWrite(C_close, HIGH);
  //    digitalWrite(pomp, HIGH);
  //    digitalWrite(A_open, HIGH);
  //    digitalWrite(B_open, HIGH);
  //
  //    digitalWrite(C_close, LOW);
  //    digitalWrite(B_close, LOW);
  //    delay(400);
  //    digitalWrite(C_close, HIGH);
  //    digitalWrite(B_close, HIGH);
  //    levelDown();
  //    pompsMid();
  //    setAngle(4, 50);
  //  } else if (data == 3) {
  //    //        Serial.println(3);
  //    levelDown();
  //    pompsDown();
  //    setAngle(4, -40);
  //    digitalWrite(A_close, HIGH);
  //    digitalWrite(A_open, LOW);
  //    digitalWrite(C_open, HIGH);
  //    digitalWrite(B_open, HIGH);
  //    digitalWrite(B_close, LOW);
  //    digitalWrite(C_close, LOW);
  //    digitalWrite(pomp, LOW);
  //    delay(2000);
  //    setAngle(4, 50);
  //    delay(1000);
  //    digitalWrite(C_close, HIGH);
  //    digitalWrite(pomp, HIGH);
  //    digitalWrite(A_open, HIGH);
  //    digitalWrite(B_open, HIGH);
  //
  //    digitalWrite(A_close, LOW);
  //    delay(400);
  //    digitalWrite(A_close, HIGH);
  //    pompsDown();
  //  } else if (data == 4) {
  //    //        Serial.println(4);
  //    levelDown();
  //    pompsDown();
  //    setAngle(4, -40);
  //    digitalWrite(A_close, HIGH);
  //    digitalWrite(A_open, LOW);
  //    digitalWrite(C_open, HIGH);
  //    digitalWrite(B_open, HIGH);
  //    digitalWrite(B_close, LOW);
  //    digitalWrite(C_close, LOW);
  //    digitalWrite(pomp, LOW);
  //    delay(2000);
  //    levelUp();
  //    setAngle(4, 50);
  //    delay(1000);
  //    digitalWrite(C_close, HIGH);
  //    digitalWrite(pomp, HIGH);
  //    digitalWrite(A_open, HIGH);
  //    digitalWrite(B_open, HIGH);
  //
  //    digitalWrite(A_close, LOW);
  //    digitalWrite(B_close, LOW);
  //    digitalWrite(C_close, LOW);
  //    levelUp();
  //    pompsDown();
  //  } else if (data == 5) {
  //    Serial.println(5);
  //    levelUp();
  //    pompsMid();
  //    setAngle(7, -50);
  //    levelDown();
  //    digitalWrite(C_close, LOW);
  //    digitalWrite(C_open, HIGH);
  //    digitalWrite(A_open, LOW);
  //    digitalWrite(B_open, LOW);
  //    digitalWrite(A_close, HIGH);
  //    digitalWrite(B_close, LOW);
  //    digitalWrite(pomp, LOW);
  //    delay(2000);
  //    levelUp();
  //    pompsDown();
  //    delay(1000);
  //    digitalWrite(pomp, HIGH);
  //    digitalWrite(A_open, HIGH);
  //    digitalWrite(B_open, HIGH);
  //
  //    digitalWrite(A_close, LOW);
  //    digitalWrite(B_close, LOW);
  //    delay(400);
  //    digitalWrite(A_close, HIGH);
  //    digitalWrite(B_close, HIGH);
  //  } else if (data == 6) {
  //    Serial.println(6);
  //    levelUp();
  //    pompsMid();
  //    digitalWrite(pomp, LOW);
  //  }
}

