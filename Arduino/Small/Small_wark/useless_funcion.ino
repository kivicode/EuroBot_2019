void smert() {
  while (1 == 1) {
    disablePomp();
    go(0, 0);
  }
}
void first_arduino () {
  //  int storon = digitalRead(storona);
  //  ///////запуск атома
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
  //go(150, 150);
  //delay(500);
  //go(0,0);
  //  lcd.setCursor(0, 0);
  //  lcd.print("ya pnul atom!65");
  //
  //  /// поворот
  //  go(-150, -150);
  //  delay(10);
  //  go(0, 0);
  //
  //  go(storon == 0 ? 0 : -150, storon == 0 ? -150 : 0);
  //  delay(50);
  //  go(storon == 0 ? -150 : 0, storon == 0 ? 0 : -150);
  //  delay(900);
  //
  //  ti = millis();
  //  while (( digitalRead(zad1) != 0) || ( digitalRead(zad2) != 0)) {
  //    go(storon == 0 ? -150 : 0, storon == 0 ? 0 : -150);
  //    if (millis() - ti > 2500) {
  //      smert();
  //    }
  //  }
}

void two_arduino() {
  int storon = digitalRead(storona);
 // takeLU();
  go(storon == 0 ? 150 : 0, storon == 0 ? 0 : 150);
  delay(50);
  go(0, 0);
  //putLU();
  lcd.setCursor(0, 0);
  lcd.print("vikinul red!65");
}
void three_arduino(int action) {
  int storon = digitalRead(storona);
//  takeLU();
  for (int i = 0; i < 6; i++) {
    go(150, 150);
    delay(10);
    go(0, 0);
    delay(40);
  };
  go(0, 0);
 // putLU();
  lcd.setCursor(0, 0);
  lcd.print("vikinul red!75");
  if (action == 2) {
    go(storon == 0 ? 150 : 0, storon == 0 ? 0 : 150);
    delay(50);
    go(0, 0);
    lcd.setCursor(0, 0);
    lcd.print("tri shaibi!600");
  }
}
