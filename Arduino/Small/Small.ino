#include <Wire.h>
#include "PCA9685.h"

const int PURPLE = 0;
const int YELLOW = 1;

int SIDE = PURPLE;


int L = 0;
int R = 1;

int starter = 47;
int switcher = 45;

PCA9685 driver;
PCA9685_ServoEvaluator pwmServo(102, 470);

int angles[5] = {0, 0, 0, 0, 0};
int pomp = 46;

#define LeftMotorBackwardPin 50
#define LeftMotorForwardPin 48
#define LeftMotorSpeedPin 51
#define LeftEncoderPin 5

#define RightMotorBackwardPin 52
#define RightMotorForwardPin 49
#define RightMotorSpeedPin 53
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
  pinMode(pomp, OUTPUT);
  pinMode(LeftMotorForwardPin, OUTPUT);
  pinMode(LeftMotorBackwardPin, OUTPUT);

  pinMode(RightMotorForwardPin, OUTPUT);
  pinMode(RightMotorBackwardPin, OUTPUT);

  pinMode(LeftMotorSpeedPin, OUTPUT);
  pinMode(RightMotorSpeedPin, OUTPUT);

  pinMode(LeftEncoderPin, INPUT_PULLUP);
  pinMode(RightEncoderPin, INPUT_PULLUP);

  pinMode(switcher,  INPUT_PULLUP);
  pinMode(starter,  INPUT_PULLUP);
  Serial.setTimeout(150);

  while (digitalRead(starter) != 0) {}

  if (digitalRead(switcher) == 1) {
    SIDE = PURPLE;
    Serial.println("PURPLE");
  } else {
    SIDE = YELLOW;
    Serial.println("YELLOW");
  }
  analogWrite(LeftMotorSpeedPin, 100);
  analogWrite(RightMotorSpeedPin, 100);
  digitalWrite(LeftMotorForwardPin, HIGH);
  digitalWrite(RightMotorForwardPin, HIGH);

  digitalWrite(LeftMotorForwardPin, LOW);
  digitalWrite(RightMotorForwardPin, LOW);

  Serial.begin(9600);
  Serial1.begin(9600);
}

/*    Команды представленны в виде имя(параметр1, параметр2)    */
void loop() {
  digitalWrite(LeftMotorBackwardPin, HIGH);
  digitalWrite(RightMotorBackwardPin, HIGH);
  digitalWrite(LeftMotorForwardPin, LOW);
  digitalWrite(RightMotorForwardPin, LOW);
  analogWrite(LeftMotorSpeedPin, 250);
  analogWrite(RightMotorSpeedPin, 250);
  delay(5000);
  digitalWrite(LeftMotorForwardPin, LOW);
  digitalWrite(RightMotorForwardPin, LOW);
  digitalWrite(LeftMotorBackwardPin, LOW);
  digitalWrite(RightMotorBackwardPin, LOW);
  delay(100000);
  //  if (Serial1.available() > 0) {
  int data = Serial1.read();
  Serial.println(data);
  //  }
  //  while (Serial.available() > 0) {  // ждём команду
  //    String in = String(Serial.readStringUntil('\n'));  // считывание строки
  //    if (in != "") {
  //      Serial.println(in);
  //      String cmd = split(in, '(', 0);  // находим имя команды
  //      String params = split(split(in, '(', 1), ')', 0);  // массив с параметрами
  //      if (cmd == "cf") {  // калибровка: вперёд
  //        Serial.print(REC);  // подтверждение принятия
  //        c_f();
  //        Serial.print(SUC);  // подтверждение выполнения
  //      }
  //      else if (cmd == "cb") {  // калибровка: назад
  //        Serial.print(REC);  // подтверждение принятия
  //        backward(2);
  //        Serial.print(SUC);  // подтверждение выполнения
  //      }
  //      else if (cmd == "cl") {  // калибровка: влево
  //        Serial.print(REC);  // подтверждение принятия
  //        left(8);
  //        Serial.print(SUC);  // подтверждение выполнения
  //      }
  //      else if (cmd == "cr") {  // калибровка: вправо
  //        Serial.print(REC);  // подтверждение принятия
  //        right(8);
  //        Serial.print(SUC);  // подтверждение выполнения
  //      }
  //      else if (cmd == "f") {
  //        int dist = split(params, ",", 0).toInt();
  //        forward(dist);
  //      }
  //      else if (cmd == "b") {
  //        int dist = split(params, ",", 0).toInt();
  //        backward(dist);
  //      }
  //      else if (cmd == "ccb") {
  //        int dist = split(params, ",", 0).toInt();
  //        backward_calib(dist);
  //      }
  //      else if (cmd == "l") {
  //        int dist = split(params, ",", 0).toInt();
  //        left(dist);
  //      }
  //      else if (cmd == "r") {
  //        int dist = split(params, ",", 0).toInt();
  //        right(dist);
  //      }
  //      else {
  //        Serial.print(in);
  //        Serial.print(REC);  // подтверждение принятия
  //        delay(100);
  //        Serial.print(ERR);
  //      }
  //    } else {
  //      Serial.print(in);
  //      Serial.print(REC);  // подтверждение принятия
  //      delay(100);
  //      Serial.print(ERR);
  //    }
  //  }
}
