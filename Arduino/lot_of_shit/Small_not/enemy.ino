float TicksInRotation = 400;
float WheelLength = 4 * PI * 2;


long int cm2tick(float cm) {
  cm /= 10.0;
  float rotates = cm / WheelLength;
  return rotates * TicksInRotation;
}

void go (int L, int R) {
  digitalWrite(LeftMotorBackwardPin, L > 0 ? LOW : HIGH);
  digitalWrite(RightMotorBackwardPin, R > 0 ? LOW : HIGH);
  digitalWrite(LeftMotorForwardPin,  L > 0 ? HIGH : LOW);
  digitalWrite(RightMotorForwardPin,  R > 0 ? HIGH : LOW);
  analogWrite(LeftMotorSpeedPin, L);
  analogWrite(RightMotorSpeedPin, R);
}

void go_by_encoders (int right_need, int left_need, int L, int R) {
  int right_ticks = 0;
  int left_ticks = 0;
  int lp = 0;
  int rp = 0;
  int r_tick = 0 ;
  int l_tick = 0;
  
  go(L, R);
  while ((right_ticks < right_need) or (left_ticks < left_need)) {
    r_tick = digitalRead(RightEncoderPin);
    l_tick = digitalRead(LeftEncoderPin);
    if (r_tick != rp) {
      right_ticks++;
      rp = r_tick;
      Serial.print("right ");
      Serial.println(right_ticks);
    }
    if (l_tick != lp) {
      left_ticks++;
      lp = l_tick;
      Serial.print("left ");
      Serial.println(left_ticks);
    }
    if (right_ticks > right_need) go(L, 0);
    if (left_ticks > left_need) go(0, R);
  }
  go(0, 0);
}

void go_by_camera (){
  
}














//void setup() {
//  Serial.begin(9600);
//}
//
//void loop() {
//  while (Serial.available() > 0) {
//    String in = String(Serial.readString());
//    Serial.println(in);
//  }
//
//}
