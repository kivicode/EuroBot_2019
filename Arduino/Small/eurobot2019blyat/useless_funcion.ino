void smert() {
  while (1 == 1) {
    go(0, 0);
  }
}

void first_arduino () {
  for (int i = 0; i < 50; i++) {
    go(150, 150);
    delay(10);
    go(0, 0);
    delay(20);
  };
    for (int j = 0; j < 25; j++) {
    go(-150, -150);
    delay(10);
    go(0, 0);
    delay(20);
  };
    for (int k = 0; k < 35; k++) {
    go(150, 150);
    delay(10);
    go(0, 0);
    delay(20);
  };
  go(0,0);
}
