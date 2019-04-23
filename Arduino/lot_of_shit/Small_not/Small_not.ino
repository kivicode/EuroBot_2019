#include <Wire.h>
#include "PCA9685.h"

int PURPLE = 0;
int YELLOW = 1;

const int SIDE = PURPLE;

char rc;
int L = 0;
int R = 1;

PCA9685 driver;
PCA9685_ServoEvaluator pwmServo(102, 470);

int angles[5] = {0, 0, 0, 0, 0};
int pomp = 46;

#define LeftMotorBackwardPin 4
#define LeftMotorForwardPin 3
#define LeftMotorSpeedPin 2
#define LeftEncoderPin 5
#define RightMotorBackwardPin 9
#define RightMotorForwardPin 8
#define RightMotorSpeedPin 7
#define RightEncoderPin 6

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
  pinMode(LeftMotorForwardPin, OUTPUT);
  pinMode(LeftMotorBackwardPin, OUTPUT);
  pinMode(RightMotorForwardPin, OUTPUT);
  pinMode(RightMotorBackwardPin, OUTPUT);
  pinMode(LeftMotorSpeedPin, OUTPUT);
  pinMode(RightMotorSpeedPin, OUTPUT);
  pinMode(LeftEncoderPin, INPUT_PULLUP);
  pinMode(RightEncoderPin, INPUT_PULLUP);
  Serial.setTimeout(150);

  disablePomp();
  setAngle(1, 45);
  setAngle(4, 10);
  ostrich();

}

/*    Команды представленны в виде имя(параметр1, параметр2)    */

void loop() {
  //опа


  //  String in = "for(100, 100)";
  //  String cmd = split(in, '(', 0);
  //  int param1 = split(split(in, '(', 1), ',', 0).toInt();
  //  int param2 = split(split(split(split(in, '(', 1), ',', 1), ')', 0), ' ', 1).toInt();
  //  go(param1, param2);

  while (Serial.available() > 0) {  // ждём команду
    String in = String(Serial.readStringUntil('\n'));  // считывание строки
    if (in != "") {
      Serial.println(in);
      String cmd = split(in, '(', 0);  // находим имя команды
      if (cmd == "cl") {
        Serial.print(REC);
        Serial.print(SUC);
      } else if (cmd == "for") {
        Serial.print(REC);
        int param1 = split(split(in, '(', 1), ',', 0).toInt();
        int param2 = split(split(split(split(in, '(', 1), ',', 1), ')', 0), ' ', 1).toInt();
        go(param1, param2);
        Serial.print(SUC);
      } else if (cmd == "veseluha") {
        Serial.print(REC);
        veseluha();
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
