// r- speed
#include <Wire.h>
#include "PCA9685.h"
PCA9685 driver;
PCA9685_ServoEvaluator pwmServo(102, 470);

int L = 0;
int R = 1;

int angles[5] = {0, 0, 0, 0, 0};

int pomp = 4  ; //13 12 35 8 9
int otpusk = 3;
#define shmor 33
#define storona 2
#define LeftMotorBackwardPin 15
#define LeftMotorForwardPin 16
#define LeftMotorSpeedPin 14
#define LeftEncoderPin 43

#define RightMotorBackwardPin 17
#define RightMotorForwardPin  18
#define RightMotorSpeedPin  19
#define RightEncoderPin 45

String SUC = "~";  // символ успешного выполнения команды (см. api.py)
String ERR = "|";  // символ ошибки выполнения команды (см. api.py)
String REC = "-";  // символ успешного принятния команды (см. api.py)

void setup() {

  Wire.begin();
  Wire.setClock(400000);
  driver.resetDevices();
  driver.init(B000000);
  driver.setPWMFrequency(50);
  Serial.begin(9600);
  Serial.println("StarT");
  pinMode(pomp, OUTPUT);
  pinMode(otpusk, OUTPUT);
  pinMode(LeftMotorForwardPin, OUTPUT);
  pinMode(LeftMotorBackwardPin, OUTPUT);
  pinMode(RightMotorForwardPin, OUTPUT);
  pinMode(RightMotorBackwardPin, OUTPUT);
  pinMode(LeftMotorSpeedPin, OUTPUT);
  pinMode(RightMotorSpeedPin, OUTPUT);
  pinMode(LeftEncoderPin, INPUT_PULLUP);
  pinMode(RightEncoderPin, INPUT_PULLUP);
  Serial.setTimeout(150);
  // go(0, 0);
  //  //test();
  //  //veseluha();
  //igitalWrite(9, HIGH);
  //  digitalWrite(50, LOW);
  //  ostrich();
  //  //go(250, 250);
//  ostrich();
//  delay(1000);
//  straight();
//  delay(1000);
//  smeh();
//  delay(3000);
//  ostrich();
//  Serial.println("Pizda");
  go(250, 250);
  delay(20000);
  go(-250, -250);
  delay(2000);
  go(250, 0);
  delay(2000);
  go(0, 250);
  delay(2000);
  go( 250, -250);
  delay(2000);
  go(0, 0);
  delay(100000);
}

void loop() {
  while (Serial.available() > 0) {  // ждём команду
    String in = String(Serial.readStringUntil('\n'));  // считывание строки
    if (in != "") {
      Serial.println(in);
      String cmd = split(in, '(', 0);  // находим имя команды

      if (cmd == "for") {
        Serial.print(REC);
        int paramL = param(in, 1);
        int paramR = param(in, 0) ;
        go (paramL, paramR);
        delay(20);
        go(0, 0);
        Serial.print(SUC);
      }
      else if (cmd == "veseluha") {
        Serial.print(REC);

        veseluha();
        Serial.print(SUC);
      }
      else if (cmd == "grab") {
        Serial.print(REC);
        int paramL = param(in, 1);
        int paramR = param(in, 0);
        grab();
        takeLU();
        Serial.print(SUC);
      }
      else {
        Serial.print(cmd);
        Serial.print(REC);
        delay(100);
        Serial.print(ERR);
      }
    }
  }
}
