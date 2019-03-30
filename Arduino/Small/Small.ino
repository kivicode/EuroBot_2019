#include <Wire.h>
#include "PCA9685.h"

int PURPLE = 0;
int YELLOW = 1;

const int SIDE = PURPLE;


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
  disablePomp();
  setAngle(1, 45);
  setAngle(4, 10);
  ostrich();

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
}

/*    Команды представленны в виде имя(параметр1, параметр2)    */
void loop() {
  while (Serial.available() > 0) {  // ждём команду
    String in = String(Serial.readStringUntil('\n'));  // считывание строки
    if (in != "") {
      String cmd = split(in, '(', 0);  // находим имя команды
      String params = split(split(in, '(', 1), ')', 0);  // массив с параметрами
      if (cmd == "cf") {  // калибровка: вперёд
        Serial.print(REC);  // подтверждение принятия
        c_f();
        Serial.print(SUC);  // подтверждение выполнения
      }
      else if (cmd == "cb") {  // калибровка: назад
        Serial.print(REC);  // подтверждение принятия
        backward(2);
        Serial.print(SUC);  // подтверждение выполнения
      }
      else if (cmd == "cl") {  // калибровка: влево
        Serial.print(REC);  // подтверждение принятия
        left(8);
        Serial.print(SUC);  // подтверждение выполнения
      }
      else if (cmd == "cr") {  // калибровка: вправо
        Serial.print(REC);  // подтверждение принятия
        right(8);
        Serial.print(SUC);  // подтверждение выполнения
      }
      else if (cmd == "f") {
        int dist = split(params, ",", 0).toInt();
        forward(dist);
      }
      else if (cmd == "b") {
        int dist = split(params, ",", 0).toInt();
        backward(dist);
      }
      else if (cmd == "ccb") {
        int dist = split(params, ",", 0).toInt();
        backward_calib(dist);
      }
      else if (cmd == "l") {
        int dist = split(params, ",", 0).toInt();
        left(dist);
      }
      else if (cmd == "r") {
        int dist = split(params, ",", 0).toInt();
        right(dist);
      }
      else if (cmd == "get") {  // калибровка: вперёд
        Serial.print(REC);  // подтверждение принятия
        take();
        Serial.print(SUC);  // подтверждение выполнения
      }
      else if (cmd == "o") {  // калибровка: вперёд
        Serial.print(REC);  // подтверждение принятия
        ostrich();
        Serial.print(SUC);  // подтверждение выполнения
      }
      else if (cmd == "s") {
        Serial.print(REC);  // подтверждение принятия
        int s = 0, a = 0;
        int n = sscanf(in.c_str() , "s(%d, %d)", &s, &a);
        setAngle(s, a);
        Serial.print(SUC);  // подтверждение выполнения
      }
      else if (cmd == "first") {
        Serial.print(REC);  // подтверждение принятия
        forward(100);
        right(10);
        Serial.print(SUC);  // подтверждение выполнения
      }
      else {
        Serial.print(in);
        Serial.print(REC);  // подтверждение принятия
        delay(100);
        Serial.print(ERR);
      }
    } else {
      Serial.print(in);
      Serial.print(REC);  // подтверждение принятия
      delay(100);
      Serial.print(ERR);
    }
  }
}
