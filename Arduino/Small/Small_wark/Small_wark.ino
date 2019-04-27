// r- speed
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <Servo.h>
#define servo00 4
#define servo11 8
#define servo22 6
#define servo33 5
#define servo44 7
int L = 0;
int R = 1;

int angles[5] = {0, 0, 0, 0, 0};

int pomp = 32;
int otpusk = 333;
#define shmor 33
#define storona 2

#define enemy_pin 3

#define LeftMotorBackwardPin 15
#define LeftMotorForwardPin 16
#define LeftMotorSpeedPin 14
#define LeftEncoderPin 43//42

#define RightMotorBackwardPin 18
#define RightMotorForwardPin  17
#define RightMotorSpeedPin  19
#define RightEncoderPin 45//44


#define zad1 31
#define zad2 30
#define forw1 38
#define forw2 39
String SUC = "~";  // символ успешного выполнения команды (см. api.py)
String ERR = "|";  // символ ошибки выполнения команды (см. api.py)
String REC = "-";  // символ успешного принятния команды (см. api.py)

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

bool use_enemy = true;
void enemy() {
  int state = digitalRead(enemy_pin);
  //  Serial.println(state);
  if (state == 1) {
    digitalWrite(LeftMotorBackwardPin,  HIGH);
    digitalWrite(RightMotorBackwardPin, HIGH);
    digitalWrite(LeftMotorForwardPin, HIGH );
    digitalWrite(RightMotorForwardPin, HIGH );
    disablePomp();
    delay(100);
    enemy();
  }
}

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(9600);
  pinMode(pomp, OUTPUT);
  pinMode(otpusk, OUTPUT);
  servo0.attach(servo00);
  servo1.attach(servo11);
  servo2.attach(servo22);
  servo3.attach(servo33);
  servo4.attach(servo44);
  if (use_enemy) {
    attachInterrupt(digitalPinToInterrupt(3), enemy, HIGH);
  }
  pinMode(LeftMotorForwardPin, OUTPUT);
  pinMode(LeftMotorBackwardPin, OUTPUT);
  pinMode(RightMotorForwardPin, OUTPUT);
  pinMode(RightMotorBackwardPin, OUTPUT);
  pinMode(LeftMotorSpeedPin, OUTPUT);
  pinMode(RightMotorSpeedPin, OUTPUT);
  pinMode(LeftEncoderPin, INPUT_PULLUP);
  pinMode(RightEncoderPin, INPUT_PULLUP);
  pinMode(zad1, INPUT_PULLUP);
  pinMode(zad2, INPUT_PULLUP);
  pinMode(forw1, INPUT_PULLUP);
  pinMode(forw2, INPUT_PULLUP);
  pinMode(storona, INPUT_PULLUP);
  Serial.setTimeout(150);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("pizza pizza pizza pizda pizda pizda");
  lcd.setCursor(0, 1);
  lcd.print("pizza pizza pizza pizda pizda pizda");
  disablePomp();
  go(0, 0);
  servo0.write(0);
//   servo1.write(20);
  

  while ( digitalRead(shmor) == 0) {
    Serial.println("Waiting...");
  }
  
  servo0.write(90);
  first_arduino();
  servo0.write(0);
  
  Serial.print(SUC);
  Serial.println("Ready");
  smert();
  delay(10000);
}



void loop() {
  //  Serial.print("shmor: ");
  //  Serial.println(digitalRead(RightEncoderPin));
  //  Serial.print("protivnik: ");
  //  enemy();
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
        delay(5);
        go(0, 0);
        delay(30);
        Serial.print(SUC);
      }
      else if (cmd == "smert") {
        Serial.print(REC);
        Serial.print(SUC);
        smert();
      }
      else if (cmd == "two_arduino") {
        Serial.print(REC);
        two_arduino();
        Serial.print(SUC);
      }
      else if (cmd == "three_arduino") {
        Serial.print(REC);
        int paramL = param(in, 1);
        int paramR = param(in, 0) ;
        three_arduino(paramL);
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
