void firstSix() {
  mov(500, 0);
  mov(100, 270);
  mov(500, 90);
  mov(100, 0);
  mov(355, 90);
  mov(100, 0);
  mov(150, 180);

  del = 1600;

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

  //  del = 1000;
  mov(250, 0);
  mov(260, 270);
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
  mov(145, 270);
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
}

void grabNearTrap() {
  del = 900;
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
}

void putOnScales() {
  mov(300, 0);
  mov(600, 180);
  mov(1000, 90);
  mov(350, 0);
  mov(240, 90);
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
}

void goToSpeeder() {
  mov(100, 0);
  mov(100, 90);
  mov(400, 180);
  pompsDown();
  right(94);
  mov(700, 0);
  right(99);
  mov(750, 0);
  mov(200, 0);
  del = 1700;
  mov(30, 270);
  mov(350, 270);
  mov(150, 0);
}

void putOnSpeeder() {
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
}

void grabBlue() {
  del = 1100;
  mov(200, 180);
  pompsDown();
  setAngle(A_level, 90);
  grabA();
  enablePomp();
  mov(115 + 320, 90);
  left(2);
  mov(400, 0);
  mov(100, 90);
  mov(100, 180);
}

void grabGoldenium() {
  //  del = 800;
  setAngle(B_level, 90);
  grabB();
  enablePomp();
  mov(317, 270);
  mov(150, 0);
}

void goBackToScales() {
  del = 900;
  right(150);
  mov(1050, 0);
  right(40);
  mov(250, 0);
  mov(250, 90);
  mov(150, 0);
  levelUp();
  mov(100, 180);
  grabA();
  grabB();
  delay(600);
  mov(150, 0);
  kickB();
  kickA();
}

void kickGoldenium() {
  kickB();
}
