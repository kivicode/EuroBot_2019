#define YELLOW 1
#define PURPLE -1

#define SIDE YELLOW

void setup() {
  Serial.begin(9600);
  initPins();
  goToPucks();
}

int p = 13;
void loop() {
}
