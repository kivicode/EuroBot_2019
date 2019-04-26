// r- speed
#include <Wire.h>
#include "PCA9685.h"
PCA9685 driver;
PCA9685_ServoEvaluator pwmServo(102, 470);
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

int L = 0;
int R = 1;

int angles[5] = {0, 0, 0, 0, 0};

int pomp = 4;
int otpusk = 3;
#define shmor 33
#define storona 2

#define LeftMotorBackwardPin 15
#define LeftMotorForwardPin 16
#define LeftMotorSpeedPin 14
#define LeftEncoderPin 43//42

#define RightMotorBackwardPin 18
#define RightMotorForwardPin  17
#define RightMotorSpeedPin  19
#define RightEncoderPin 45//44

#define enemy_pin 0

#define zad1 31
#define zad2 30
#define forw1 38
#define forw2 39
String SUC = "~";  // символ успешного выполнения команды (см. api.py)
String ERR = "|";  // символ ошибки выполнения команды (см. api.py)
String REC = "-";  // символ успешного принятния команды (см. api.py)

void enemy() {
  go(0, 0);
  disablePomp();
  delay(100);
  if (digitalRead(enemy_pin) == 0) {
    enemy();
  }
}

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
  attachInterrupt(enemy_pin, enemy, CHANGE);
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
  //  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
  //    // scroll one position left:
  //    lcd.scrollDisplayLeft();
  //    // wait a bit:
  //    delay(150);
  //  }

  disablePomp();
  //  ostrich();
  while (1 == 1) {

    go(-150,-250);
    delay(3000);
  }
  ostrich();
  smeh();
  for (int i = 0; i < 20; i++) {
    go(150, 150);
    delay(10);
    go(0, 0);
    delay(40);
  };
  go(-150, -150);
  delay(10);
  go(0, 0);


  go(0, -150);
  delay(50);
  go(-150, 0);
  delay(900);
  while (( digitalRead(zad1) != 0) || ( digitalRead(zad2) != 0)) {
    go(-150, 0);
  }
  go(0, 0);
  //test();
}



void loop() {
  // Serial.println(digitalRead(zad2));


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
      else if (cmd == "shaiba") {
        Serial.print(REC);
        int paramL = param(in, 1);
        int paramR = param(in, 0) ;
        go (paramL, paramR);
        delay(5);
        go(0, 0);
        delay(30);
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
      else if (cmd == "turn_one") {
        Serial.print(REC);
        int paramL = param(in, 1);
        turn_one(paramL);
        //         Serial.print(SUC);
      }
      else if (cmd == "storona") {
        Serial.print(REC);
        if (digitalRead(storona) == 1) {
          Serial.println("purple");
        } else {
          Serial.println("orange");
        }
        //        Serial.print(SUC);
      }
      else if (cmd == "shmor") {
        Serial.print(REC);
        if (digitalRead(storona) == 1) {
          Serial.println("ready");
        } else {
          Serial.println("pizda//");
        }
        //        Serial.print(SUC);
      }
      else if (cmd == "smert") {
        Serial.print(REC);
        Serial.print(SUC);
        ostrich();
        while (1 == 1) {
          disablePomp();
          go(0, 0);
        }
      }
      else if (cmd == "take") {
        Serial.print(REC);
        takeLU();
        Serial.print(SUC);
      }
      else if (cmd == "take") {
        Serial.print(REC);
        int paramL = param(in, 1);
        int paramR = param(in, 0) ;
        shaiba_v_ebalo(paramL);
        Serial.print(SUC);
      }
      else if (cmd == "turn_two") {
        Serial.print(REC);
        int paramL = param(in, 1);
        turn_two(paramL);
        Serial.print(SUC);
      }
      else if (cmd == "turn_three") {
        Serial.print(REC);
        go (150, 150);
        delay(50);
        go(0, 0);
        go (150, 150);
        delay(50);
        go(0, 0);
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
