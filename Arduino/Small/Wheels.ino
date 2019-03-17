
float TicksInRotation = 400;
float WheelRadius = 4;
float WheelLength = WheelRadius * PI * 2;

void forward(int dist) {

  long int ticks = cm2tick(dist);
  Serial.println(ticks);
  analogWrite(LeftMotorSpeedPin, 100);
  analogWrite(RightMotorSpeedPin, 120);

  digitalWrite(LeftMotorForwardPin, HIGH);
  digitalWrite(RightMotorForwardPin, HIGH);
  go(ticks);

  digitalWrite(LeftMotorForwardPin, LOW);
  digitalWrite(RightMotorForwardPin, LOW);
}

void backward(int dist) {

  long int ticks = cm2tick(dist);
  Serial.println(ticks);
  analogWrite(LeftMotorSpeedPin, 100);
  analogWrite(RightMotorSpeedPin, 120);

  digitalWrite(LeftMotorBackwardPin, HIGH);
  digitalWrite(RightMotorBackwardPin, HIGH);
  go(ticks);

  digitalWrite(LeftMotorBackwardPin, LOW);
  digitalWrite(RightMotorBackwardPin, LOW);
}

void left(int dist) {

  long int ticks = cm2tick(dist);
  Serial.println(ticks);
  analogWrite(LeftMotorSpeedPin, 200);
  analogWrite(RightMotorSpeedPin, 220);

  digitalWrite(LeftMotorBackwardPin, HIGH);
  digitalWrite(RightMotorForwardPin, HIGH);
  go(ticks);

  digitalWrite(LeftMotorBackwardPin, LOW);
  digitalWrite(RightMotorForwardPin, LOW);
}

void right(int dist) {

  long int ticks = cm2tick(dist);
  Serial.println(ticks);
  analogWrite(LeftMotorSpeedPin, 200);
  analogWrite(RightMotorSpeedPin, 220);

  digitalWrite(LeftMotorForwardPin, HIGH);
  digitalWrite(RightMotorBackwardPin, HIGH);
  go(ticks);

  digitalWrite(LeftMotorForwardPin, LOW);
  digitalWrite(RightMotorBackwardPin, LOW);
}

long int cm2tick(int cm){
  float rotates = (float)cm / (float)WheelLength;
  return rotates * TicksInRotation;
}

void go(int ticks){
  int counterL = 0;
  int lStateL = 0;
  int counterR = 0;
  int lStateR = 0;
  while (counterL <= ticks && counterR <= ticks) {
    int sL = digitalRead(LeftEncoderPin);
    if (sL != lStateL) {
      lStateL = sL;
      counterL++;
    }

    int sR = digitalRead(LeftEncoderPin);
    if (sR != lStateR) {
      lStateR = sR;
      counterR++;
    }
  }
}

