/*        */
#define LeftMotorBackwardPin 4
#define LeftMotorForwardPin 3
#define LeftMotorSpeedPin 2
#define LeftEncoderPin 5

#define RightMotorBackwardPin 9
#define RightMotorForwardPin 8
#define RightMotorSpeedPin 7
#define RightEncoderPin 6

void setup() {
  Serial.begin(9600);

  /*         */
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


String SUC = "~";  // символ успешного выполнения команды (см. api.py)
String ERR = "|";  // символ ошибки выполнения команды (см. api.py)
String REC = "-";  // символ успешного принятния команды (см. api.py)


/*    Команды представленны в виде имя(параметр1, параметр2)    */
void loop() {
  while (Serial.available() > 0) {  // ждём команду
    String in = String(Serial.readStringUntil('\n'));  // считывание строки
    if (in != "") {
      String cmd = split(in, '(', 0);  // находим имя команды
      String params = split(split(in, '(', 1), ')', 0);  // массив с параметрами
      if (cmd == "cf") {  // калибровка: вперёд
        Serial.print(REC);  // подтверждение принятия
        forward(2);
        Serial.print(SUC);  // подтверждение выполнения
      }
      else if (cmd == "cb") {  // калибровка: назад
        Serial.print(REC);  // подтверждение принятия
        backward(2);
        Serial.print(SUC);  // подтверждение выполнения
      }
      else if (cmd == "cl") {  // калибровка: влево
        Serial.print(REC);  // подтверждение принятия
        left(1);
        Serial.print(SUC);  // подтверждение выполнения
      }
      else if (cmd == "cr") {  // калибровка: вправо
        Serial.print(REC);  // подтверждение принятия
        right(1);
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
