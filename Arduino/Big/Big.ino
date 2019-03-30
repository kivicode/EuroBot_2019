void setup() {
  Serial.begin(9600);
  initPins();
  forward(220);
//  delay(1000);
  diagRF(1500);
//  delay(1000);
  right(100);
//  delay(1000);
  forward(200);
  delay(1000);
  rotateL(12);
}

int p = 13;
void loop() {
}
