float TicksInRotation = 400;
float WheelLength = 4 * PI * 2;

long int cm2tick(float cm) {
  cm /= 10.0;
  float rotates = cm / WheelLength;
  return rotates * TicksInRotation;
}

void go (int L, int R) { //work
  digitalWrite(LeftMotorBackwardPin, L > 0 ? LOW : HIGH);
  digitalWrite(RightMotorBackwardPin, R > 0 ? LOW : HIGH);
  digitalWrite(LeftMotorForwardPin,  L > 0 ? HIGH : LOW);
  digitalWrite(RightMotorForwardPin,  R > 0 ? HIGH : LOW);
  analogWrite(LeftMotorSpeedPin, abs(L));
  analogWrite(RightMotorSpeedPin, abs(R));
}

void go_by_encoders (int left_need, int right_need, int L, int R) { //maybe work
  int right_ticks = 0;
  int left_ticks = 0;
  int lp = 0;
  int rp = 0;
  int r_tick = 0 ;
  int l_tick = 0;
  int len = 5;
  while ((right_ticks < right_need) or (left_ticks < left_need)) {
    int right_ticks_loc = 0, left_ticks_loc = 0;
    go(0, R);
    while (right_ticks_loc < len) {
      r_tick = digitalRead(RightEncoderPin);
      if (r_tick != rp) {
        right_ticks_loc++;
        rp = r_tick;
      }
    }
    right_ticks += len;
    go(L, 0);

    while (left_ticks_loc < len) {
      l_tick = digitalRead(LeftEncoderPin);
      if (l_tick != lp) {
        left_ticks_loc++;
        lp = l_tick;
      }
    }
    left_ticks += len;
  }
  go(0, 0);
  //  while ((right_ticks < right_need) or (left_ticks < left_need)) {
  //    go(L, R);
  //    r_tick = digitalRead(RightEncoderPin);
  //    l_tick = digitalRead(LeftEncoderPin);
  //    if (r_tick != rp) {
  //      right_ticks++;
  //      rp = r_tick;
  //      Serial.print("right ");
  //      Serial.println(right_ticks);
  //    }
  //    if (l_tick != lp) {
  //      left_ticks++;
  //      lp = l_tick;
  //      Serial.print("left ");
  //      Serial.println(left_ticks);
  //    }
  //    if (right_ticks >= right_need) R = 0;
  //    if (left_ticks >= left_need) L = 0;
  //  }
  //  go(0, 0);
}
