#define F HIGH
#define B LOW

bool disabled[] = {false, false, false, false};

void goToPucks() {
  if (SIDE == PURPLE) {
    
  } else {
    //    forward(220);
    //    diagLF(1500);
    //    left(100);
    //    forward(200);
    //    rotateR(12);
  }
}


void initPins() {
  for (int i = 0; i < 4; i++) {
    pinMode(stp[i], OUTPUT);
    pinMode(dir[i], OUTPUT);
  }
}

void setDir(int m, int d) {
  digitalWrite(dir[m - 1], m > 2 ? 1 - d : d);
}

void resetDisabled() {
  for (int i = 0; i < 4; i++) {
    disabled[i] = false;
  }
}

void forward(int mm) {
  resetDisabled();
  setDir(1, F);
  setDir(2, F);
  setDir(3, F);
  setDir(4, F);
  go((50.0 / 35.0)*mm);
}

void backward(int mm) {
  resetDisabled();
  setDir(1, B);
  setDir(2, B);
  setDir(3, B);
  setDir(4, B);
  go((50.0 / 35.0)*mm);
}

void right(int mm) {
  resetDisabled();
  setDir(1, B);
  setDir(2, F);
  setDir(3, B);
  setDir(4, F);
  go(0.8 * 2.04 * mm);
}

void left(int mm) {
  resetDisabled();
  setDir(1, F);
  setDir(2, B);
  setDir(3, F);
  setDir(4, B);
  go(0.8 * 2.04 * mm);
}

void diagLB(int mm) {
  resetDisabled();
  disabled[0] = true;
  disabled[2] = true;
  setDir(2, B);
  setDir(4, B);
  go(1.8 * mm);
}

void diagRF(int mm) {
  resetDisabled();
  disabled[0] = true;
  disabled[2] = true;
  setDir(2, F);
  setDir(4, F);
  go(mm * 1.8);
}

void diagLF(int mm) {
  resetDisabled();
  disabled[1] = true;
  disabled[3] = true;
  setDir(1, F);
  setDir(3, F);
  go(1.8 * mm);
}

void diagRB(int mm) {
  resetDisabled();
  disabled[1] = true;
  disabled[3] = true;
  setDir(1, B);
  setDir(3, B);
  go(1.8 * mm);
}

void rotateL(int deg) {
  resetDisabled();
  setDir(1, F);
  setDir(2, F);
  setDir(3, B);
  setDir(4, B);
  go((40.0 / 9.0)*deg);
}

void rotateR(int deg) {
  resetDisabled();
  setDir(1, B);
  setDir(2, B);
  setDir(3, F);
  setDir(4, F);
  go((40.0 / 9.0)*deg);
}

void go(int ticks) {
  int lspd = spd * 2;
  int period = 400;
  for (int i = 0; i < ticks; i++) {
    if (i < period) {
      lspd--;
    }
    for (int i = 0; i < 4; i++) {
      if (disabled[i] == false) {
        digitalWrite(stp[i], HIGH);
      }
    }
    delayMicroseconds(lspd);
    for (int i = 0; i < 4; i++) {
      if (disabled[i] == false) {
        digitalWrite(stp[i], LOW);
      }
    }
    delayMicroseconds(lspd);
  }
}
