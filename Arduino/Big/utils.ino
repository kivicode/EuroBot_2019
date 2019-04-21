bool disabled[] = {false, false, false, false};

int speeds[] = {0, 0, 0, 0};
int t = 0;


void initPins() {
  for (int i = 0; i < 4; i++) {
    pinMode(stp[i], OUTPUT);
    pinMode(dir[i], OUTPUT);
  }

  for (int i = 38; i <= 50; i += 2) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void resetDisabled() {
  for (int i = 0; i < 4; i++) {
    speeds[i] = 1;
  }
}


void check() {
  if (Serial3.read() > 0) {
    Serial.println("Stop");
    delay(1000);
    check();
  } else {
    Serial.println("Start");
  }
}

void right(int mm) {
  resetDisabled();
  setDir(1, B);
  setDir(2, B);
  setDir(3, F);
  setDir(4, F);
  go(1.6 * 2.04 * mm / 0.3888);
}

void left(int mm) {
  resetDisabled();
  setDir(1, F);
  setDir(2, F);
  setDir(3, B);
  setDir(4, B);
  go(1.6 * 2.04 * mm / 0.3888);
}

void mov(float dist, double angle) {
  int goal = 0;

  t = 0;
  dist *= 6.8965517241;
  m.move_straight(angle / 180. * acos(-1), dist);
  if (m.get_steps(1) < 0) {
    speeds[1] = 1;
    speeds[3] = 1;
    setDir(2, B);
    setDir(4, B);
    goal = abs(m.get_steps(1));
  } else if (m.get_steps(1) > 0) {
    speeds[1] = 1;
    speeds[3] = 1;
    setDir(2, F);
    setDir(4, F);
    goal = m.get_steps(1);
  } else {
    speeds[1] = 0;
    speeds[3] = 0;
  }

  if (m.get_steps(2) < 0) {
    speeds[0] = 1;
    speeds[2] = 1;
    setDir(1, B);
    setDir(3, B);
    goal = abs(m.get_steps(2));
  } else if (m.get_steps(2) > 0) {
    speeds[0] = 1;
    speeds[2] = 1;
    setDir(1, F);
    setDir(3, F);
    goal = m.get_steps(2);
  } else {
    speeds[0] = 0;
    speeds[2] = 0;
  }

  go(goal);
}

void go(int goal) {
  for (int t = 0; t < goal; t++) {
    for (int i = 0; i < 4; i++) {
      if (speeds[i] != 0) {
        digitalWrite(stp[i], t % 2 == 0 ? HIGH : LOW);
      }
    }
    delayMicroseconds(del);
  }
}

int k = 0;
void kickTwo() {
  del = 1600;
  if (k == 0) {
    levelDown();
  } else {
    setAngle(C_level, 90);
    setAngle(B_level, -90);
  }
  mov(100, 0);
  mov(k == 0 ? 75 : 103, 180);
  if (k == 1) {
    right(3);
  }
  if (k == 0) {
    mov(30, 90);
  } else {
    mov(50, 270);
  }
  digitalWrite(B_grab, LOW);
  digitalWrite(B_kick, HIGH);
  digitalWrite(C_grab, LOW);
  digitalWrite(C_kick, HIGH);
  enablePomp();
  setAngle(B_level, 90);
  setAngle(C_level, -40);
  grabB();
  setAngle(B_pomp, 0);
  grabC();
  setAngle(C_pomp, 65);
  delay(500);
  mov(100, 0);
  mov(24, 180);
  delay(500);
  disablePomp();
  levelDown();
  delay(500);
  kickC();
  kickB();
  levelUp();
  delay(500);
  mov(100, 180);
  k++;
}
