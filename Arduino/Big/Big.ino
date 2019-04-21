#include <TimerOne.h>

#include <Movement.h>

#include <SoftwareSerial.h>
#include <Wire.h>
#include "PCA9685.h"

#define YELLOW 1
#define PURPLE -1

PCA9685 driver;
PCA9685_ServoEvaluator pwmServo(102, 470);

int SIDE;

#define F HIGH
#define B LOW

const int take = 1;

int del = 800;

int stp[] = {22, 24, 26, 28};
int dir[] = {30, 32, 34, 36};

int pomp = 38;

int C_kick = 40;
int B_kick = 42;
int A_kick = 44;

int A_grab = 46;
int B_grab = 48;
int C_grab = 50;

int C_level = 1;
int B_level = 2;
int A_level = 3;

int C_pomp = 6;
int B_pomp = 5;
int A_pomp = 4;

Movement m;

void setDir(int m, int d) {
  digitalWrite(dir[m - 1], m > 2 ? 1 - d : d);
}
void setup() {
  initPins();
  Wire.begin();
  Wire.setClock(400000);
  driver.resetDevices();
  driver.init(B000000);
  driver.setPWMFrequency(50);
  //  Serial.begin(9600);
  //  Serial3.begin(9600);

  pompsDown();
  levelDown();

  m.set_wheel_rad(60); //радиус колеса
  m.set_steps_per_turn(200); //шагов на оборот шаговика
  m.set_steps_mod(0.785);
  m.set_speed(1);
  /*
    //-------------------- Езда до первых 6 шайб --------------------
    mov(600, 0);
    mov(100, 270);
    mov(500, 90);
    mov(100, 0);
    mov(230, 90);
    mov(100, 0);
    mov(150, 180);


    pompsMid();
    enablePomp();
    grabA();
    grabB();
    kickC();
    mov(200, 0);
    delay(500);
    mov(200, 180);
    pompsDown();
    delay(700);
    kickA();
    kickB();
    disablePomp();
    left(5);


    mov(250, 0);
    mov(200, 270);
    mov(120, 0);
    mov(200, 180);
    left(2);

    pompsMid();
    enablePomp();
    grabA();
    grabB();
    kickC();
    mov(250, 0);
    delay(500);
    mov(220, 180);
    pompsDown();
    delay(700);
    kickA();
    kickB();
    disablePomp();
    left(5);

    mov(300, 0);
    mov(102, 270);
    mov(90, 0);
    mov(100, 180);
    pompsMid();
    enablePomp();
    kickA();
    kickB();
    grabC();
    delay(700);
    mov(200, 0);
    delay(500);
    mov(150, 180);
    pompsDown();
    delay(700);
    kickC();

    mov(113, 90);
    grabC();
    delay(200);
    mov(200, 0);
    delay(200);
    mov(200, 180);
    pompsDown();
    delay(300);
    kickC();
    disablePomp();
    levelUp();

    // -------------------- Езда до шайб у горки --------------------
    kickA();
    kickB();
    kickC();
    delay(300);
    levelDown();
    setAngle(A_level, -50);
    setAngle(B_level, -70);
    setAngle(C_level, 70);
    mov(400, 270);
    right(15);
    mov(400, 270);
    mov(920, 0);
    mov(250, 270);
    levelUp();
    delay(400);
    pompsMid();
    mov(100, 180);
    levelDown();
    mov(100, 90);
    left(6);
    enablePomp();
    grabB();
    grabC();
    kickA();
    levelDown();
    delay(300);
    mov(350, 0);
    delay(300);
    mov(150, 180);
    levelUp();
    pompsDown();
    delay(300);
    kickB();
    kickC();
    disablePomp();


    //-------------------- Езда до ускорителя у горки --------------------
    mov(100, 0);
    mov(600, 180);
    mov(990, 90);
    mov(350, 0);
    mov(250, 90);
    mov(100, 0);
    mov(150, 180);
    mov(45, 270);
    left(5);
    levelUp();
    enablePomp();
    delay(300);
    setAngle(A_level, -40);
    setAngle(B_level, -50);
    digitalWrite(A_grab, LOW);
    digitalWrite(A_kick, HIGH);
    digitalWrite(B_grab, LOW);
    digitalWrite(B_kick, HIGH);
    delay(500);
    levelUp();
    pompsMid();
    setAngle(C_pomp, -40);
    setAngle(A_level, 65);
    setAngle(B_level, 45);
    setAngle(A_pomp, -20);
    setAngle(B_pomp, 20);
    delay(500);
    mov(200, 0);
    disablePomp();
    digitalWrite(A_grab, HIGH);
    digitalWrite(A_kick, LOW);
    digitalWrite(B_grab, HIGH);
    digitalWrite(B_kick, LOW);
    delay(1000);
    mov(100, 180);
    mov(30, 270);
    levelDown();
    pompsDown();
    delay(300);
    setAngle(A_level, -75);
    kickB();
    kickC();
    enablePomp();
    delay(700);
    digitalWrite(A_grab, LOW);
    digitalWrite(A_kick, HIGH);
    setAngle(A_level, 65);
    setAngle(A_pomp, -20);
    delay(900);
    mov(100, 0);
    disablePomp();
    digitalWrite(A_grab, HIGH);
    digitalWrite(A_kick, LOW);
    delay(1000);
    mov(100, 180);


    //-------------------- Езда от весов к ускорителю --------------------
    mov(400, 180);
    right(90);
    mov(700, 0);
    right(93);
    mov(750, 0);
    mov(200, 0);
    del = 1700;
    mov(30, 270);
    mov(90, 270);
    mov(50, 0);


  */
  //-------------------- Выгрузка шайб на ускоритель --------------------
  kickTwo();
  del = 800;
  mov(250, 0);
  levelUp();
  delay(700);
  levelDown();
  delay(500);
  kickTwo();
  mov(40, 90);
  enablePomp();
  setAngle(C_level, 200);
  digitalWrite(C_grab, LOW);
  digitalWrite(C_kick, HIGH);
  delay(1300);
  grabC();
  setAngle(C_level, -40);
  delay(500);
  mov(170, 0);
  mov(24, 180);
  delay(500);
  disablePomp();
  levelDown();
  delay(500);
  kickC();
  delay(500);
  mov(100, 180);

  //-------------------- Захват голдениума --------------------
  setAngle(B_level, 90);
  grabB();
  enablePomp();
  mov(290, 270);
  mov(150, 0);
  mov(200, 180);


}


void loop() {
}
