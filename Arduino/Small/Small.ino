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
//  test();
}

/*    Команды представленны в виде имя(параметр1, параметр2)    */
void loop() {
  while (Serial.available() > 0) {  // ждём команду
    String in = String(Serial.readStringUntil('\n'));  // считывание строки
    if (in != "") {
      Serial.println(in);
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
      else if (cmd == "t") {

      } else if (cmd == "t") {
        setAngle(0, 0);
        setAngle(1, 80);
        setAngle(3, 40);
        delay(1000);
        straight();
        delay(500);
        grab(0, 0.25, 0.9);
        delay(1000);
        straight();
        delay(1000);
        enablePomp();
        setAngle(1, 60);
        setAngle(2, -40);
        setAngle(3, -85);
        setAngle(4, -20);
        delay(1000);
        setAngle(0, 30);
        setAngle(1, 35);
        setAngle(2, -60);
        setAngle(3, -60);
        setAngle(4, -30);
        delay(300);
        setAngle(2, -75);
        delay(300);
        disablePomp();
        setAngle(0, -10);
        delay(1000);
        setup();
      } else if (cmd == "p") {
        setAngle(0, 0);
        setAngle(1, 80);
        setAngle(3, 40);
        delay(1000);
        straight();
        delay(500);
        grab(0, 0.25, 0.9);
        delay(1000);
        straight();
        delay(1000);
        enablePomp();
        setAngle(1, 60);
        setAngle(2, -40);
        setAngle(3, -85);
        setAngle(4, -20);
        delay(1000);
        setAngle(0, -30);
        setAngle(1, 35);
        setAngle(2, -60);
        setAngle(3, -60);
        setAngle(4, -30);
        delay(300);
        setAngle(2, -75);
        delay(300);
        disablePomp();
        setAngle(0, 10);
        delay(1000);
        setup();
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
