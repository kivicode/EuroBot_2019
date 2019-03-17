/*    Пины    */
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

  /*    Инициализация пинов    */
  pinMode(LeftMotorForwardPin, OUTPUT);
  pinMode(LeftMotorBackwardPin, OUTPUT);

  pinMode(RightMotorForwardPin, OUTPUT);
  pinMode(RightMotorBackwardPin, OUTPUT);

  pinMode(LeftMotorSpeedPin, OUTPUT);
  pinMode(RightMotorSpeedPin, OUTPUT);

  pinMode(LeftEncoderPin, INPUT_PULLUP);
  pinMode(RightEncoderPin, INPUT_PULLUP);

  Serial.setTimeout(150); // Что бы не было задержки при приёме строк
}


String SUCC = "~";  // символ успешного выполнения команды (см. api.py)


/*    Команды представленны в виде имя(параметр1, параметр2)    */
void loop() {
  while (Serial.available() > 0) {  // ждём команду
    String in = String(Serial.readString());  // считывание строки
    if (in != "") {
      String cmd = split(in, '(', 0);  // находим имя команды
      String params = split(split(in, '(', 1), ')', 0);  // массив с параметрами
      if (cmd == "cf") {  // калибровка: вперёд
        forward(2);
        Serial.print(SUCC);  // подтверждение выполнения
      }
      else if (cmd == "cb") {  // калибровка: назад
        backward(2);
        Serial.print(SUCC);  // подтверждение выполнения
      }
      else if (cmd == "cl") {  // калибровка: влево
        left(1);
        Serial.print(SUCC);  // подтверждение выполнения
      }
      else if (cmd == "cr") {  // калибровка: вправо
        right(1);
        Serial.print(SUCC);  // подтверждение выполнения
      }
    }
  }
}
