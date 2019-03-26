void setAngle_(int servo_id, int angle) {
  driver.setChannelPWM(servo_id, pwmServo.pwmForAngle(angle));
}
void setAngle(int servo_id, int angle, int del) {
  if (del == 0) {
    setAngle_(servo_id, angle);
    angles[servo_id] = angle;
    return;
  }

  int prev = angles[servo_id];
  int curr = angle;

  if (prev < curr) {
    for (int a = prev; a <= curr; ++a) {
      setAngle_(servo_id, a);
      delay(del);
    }
  } else {
    for (int a = prev; a > curr; --a) {
      setAngle_(servo_id, a);
      delay(del);
    }
  }

  angles[servo_id] = curr;
}
void setAngle(int servo_id, int angle) {
  setAngle(servo_id, -angle, 0);
  angles[servo_id] = angle;
}

void startPark() {
  setAngle(1, -30);
  setAngle(2, 20);
  setAngle(3, 80);
  setAngle(4, 60);
}

void park() {
  setAngle(1, -30);
  setAngle(2, 20);
  setAngle(3, 80);
  setAngle(4, 40);
}

void straight() {
  setAngle(0, 0);
  for (int i = 1; i < 5; ++i) {
    setAngle(i, 10);
    delay(10);
  }
}

void enablePomp() {
  digitalWrite(pomp, LOW);
}

void disablePomp() {
  digitalWrite(pomp, HIGH);
}

void ostrich() {  // спрятал голову в песок
  setAngle(1, 75);
  setAngle(2, -65);
  setAngle(3, -78);
  delay(1000);
  setAngle(0, 80);
}

void putUp(int dir) {
  setAngle(0, dir == L ? 20 : -12); // L - 20
  setAngle(1, -5); // L - -5
  setAngle(2, dir == L ? -20 : -25);
  setAngle(3, dir == L ? -45 : -50); //L - -45
}

void putDown(int dir) {
  setAngle(0, dir == L ? 25 : -20); // L - 20
  setAngle(1, dir == L ? 40 : 35); // L - -5
  setAngle(2, dir == L ? -90 : -90);
  setAngle(3, dir == L ? -45 : -45); //L - -45
}

void grab(int angle, double distance, double height) {
  setAngle(0, angle, 10);

  delay(400);

  double a1 = 30 + 50 * distance;
  double a2 =  0 + 50 * (1 - distance);
  double a4 = 20 + 38 * distance;

  a1 -= 10 * height;
  a4 += 10 * height;

  setAngle(4, 20);
  delay(100);
  setAngle(1, a1);
  setAngle(2, a2);
  setAngle(3, a2);
}

void take() {
  setAngle(0, 0);
  setAngle(1, 80);
  setAngle(3, 40);
  delay(1000);
  straight();
  delay(500);
  enablePomp();

  grab(0, 0.25, 0.9);

  delay(1000);
  straight();
  delay(1000);
  setAngle(1, 60);
  setAngle(2, -40);
  setAngle(3, -85);
  setAngle(4, -20);
  delay(2000);
  setAngle(0, 13);
  setAngle(1, 35);
  setAngle(1, 0);
  setAngle(3, -45);
  delay(2000);
  setAngle(1, -5);
  setAngle(2, -20);
  setAngle(4, -30);

  delay(1000);

  disablePomp();

  setAngle(1, 5);

  //  setAngle(1, 45);
  //  setAngle(4, 10);
  //  ostrich();
  ////
  //  setAngle(0, 0);
  //  setAngle(1, 80);
  //  setAngle(2, 45);
}

void take_test() {
  //  straight();
  //  delay(1000);
  //  enablePomp();
  setAngle(0, 0);
  setAngle(1, 0);
  delay(1000);
  straight();
  //  setAngle .(2, 45);

  delay(1000);
  //  grab(0, 0.2, 0.9);
  //  delay(1000);
  //  disablePomp();
  straight();

  delay(1000);

  setAngle(1, 60);
  setAngle(2, -15);
  setAngle(3, -60);

  delay(1000);

  setAngle(0, 20);
  setAngle(3, -60);
  setAngle(1, 0);

  delay(1000);
  //  delay(3000);
  //  putUp(L);
  //  delay(100);
  //  disablePomp();
  //  delay(2600);
  //  setAngle(0, -5, 10);
  //  delay(500);
  //  straight();
}
