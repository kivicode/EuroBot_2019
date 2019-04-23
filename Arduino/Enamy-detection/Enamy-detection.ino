const int trigs[6] = {8, 9, 10, 11, 12, 13};
const int echos[6] = {2, 3, 4,  5,  6,  7};
//4 eh, 10
//5, 11 
//6, 12
const int MAX_DIST = 25;

long duration;
int distance = 10e9;

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(trigs[i], OUTPUT);
    pinMode(echos[i], INPUT);
  }
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  Serial.begin(9600);
}

bool stopped = false;

void loop() {
  distance = 10e9;
  for (int i = 0; i < 6; i++) {
    digitalWrite(trigs[i], LOW);
    delayMicroseconds(2);

    digitalWrite(trigs[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigs[i], LOW);

    duration = pulseIn(echos[i], HIGH);
    int dst = duration * 0.034 / 2;
    Serial.println((String)i + " " + (String)dst);
  }

//  if (distance < MAX_DIST || !stopped) {
//        Serial.println(distance);
//    digitalWrite(A1, HIGH);
//    stopped = true;
//  } else if (stopped && distance >= MAX_DIST) {
//    //    Serial.println("Go");
//    digitalWrite(A1, LOW);
//    stopped = false;
//  }
}
