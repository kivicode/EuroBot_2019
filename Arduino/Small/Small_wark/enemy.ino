

void turn_two(int storon) {
  long star = millis();
  while ((millis() - star > 1000)) {
    go(storon == 0 ? 150 : 0, storon == 0 ? 0 : 150);
    delay(20);
    go(0, 0);
    delay(40);
  }
  Serial.print(SUC);
  go(0, 0);
}
void go_by_forw() {
  long star = millis();
  int suck = 0;
  while (( digitalRead(forw1) != 0) || ( digitalRead(forw2) != 0)) {
    go(150, 150);
    if (millis() - star > 2000) {
      Serial.print(ERR);
      go(0, 0);
      suck = 1;
      break;
    }
  }
  if (suck != 1) Serial.print(SUC);
  go(0, 0);
}
