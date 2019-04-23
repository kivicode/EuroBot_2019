

//
//int total_ticks = 0;
//
//void forward(int dist) {
//  int times = dist / 2;
//  total_ticks = 0;
//  for (int i = 0; i < times; i++) {
//    cf(true);
//  }
//}
//
//void cf (bool smooth) {
//  long int ticks = cm2tick(2);
//  //  analogWrite(LeftMotorSpeedPin, SIDE == PURPLE ? 90 : 60);
//  //  analogWrite(RightMotorSpeedPin, SIDE == PURPLE ? 60 : 100);
//
//  digitalWrite(LeftMotorForwardPin, HIGH);
//  digitalWrite(RightMotorForwardPin, HIGH);
//  if (!smooth) {
//    total_ticks = 0;
//  }
//  go(ticks, SIDE == PURPLE ? 200 : 120, SIDE == PURPLE ? 60 : 100, false);
//
//  digitalWrite(LeftMotorForwardPin, LOW);
//  digitalWrite(RightMotorForwardPin, LOW);
//}
//
//void c_f() {
//  int dist = 8;
//  int times = dist / 2;
//  total_ticks = 0;
//  for (int i = 0; i < times; i++) {
//    cf(false);
//  }
//}
//
//void backward(int dist) {
//
//  long int ticks = cm2tick(dist);
//  analogWrite(LeftMotorSpeedPin, 200);
//  analogWrite(RightMotorSpeedPin, 90);
//
//  digitalWrite(LeftMotorBackwardPin, HIGH);
//  digitalWrite(RightMotorBackwardPin, HIGH);
//  go(ticks, SIDE == PURPLE ? 100 : 60, SIDE == PURPLE ? 60 : 100, false);
//
//  digitalWrite(LeftMotorBackwardPin, LOW);
//  digitalWrite(RightMotorBackwardPin, LOW);
//}
//
//void backward_calib(int dist) {
//
//  analogWrite(LeftMotorSpeedPin, 200);
//  analogWrite(RightMotorSpeedPin, 90);
//
//  digitalWrite(LeftMotorBackwardPin, HIGH);
//  digitalWrite(RightMotorBackwardPin, HIGH);
//  delay(dist);
//
//  digitalWrite(LeftMotorBackwardPin, LOW);
//  digitalWrite(RightMotorBackwardPin, LOW);
//}
//
//void left(int dist) {
//
//  long int ticks = cm2tick(dist);
//  analogWrite(LeftMotorSpeedPin, 200);
//  analogWrite(RightMotorSpeedPin, 90);
//
//  digitalWrite(LeftMotorBackwardPin, HIGH);
//  digitalWrite(RightMotorForwardPin, HIGH);
//  go(ticks, SIDE == PURPLE ? 100 : 60, SIDE == PURPLE ? 60 : 100, false);
//
//  digitalWrite(LeftMotorBackwardPin, LOW);
//  digitalWrite(RightMotorForwardPin, LOW);
//}
//
//void right(int dist) {
//
//  long int ticks = cm2tick(dist);
//  analogWrite(LeftMotorSpeedPin, 200);
//  analogWrite(RightMotorSpeedPin, 90);
//
//  digitalWrite(LeftMotorForwardPin, HIGH);
//  digitalWrite(RightMotorBackwardPin, HIGH);
//  go(ticks, SIDE == PURPLE ? 100 : 60, SIDE == PURPLE ? 60 : 100, false);
//
//  digitalWrite(LeftMotorForwardPin, LOW);
//  digitalWrite(RightMotorBackwardPin, LOW);
//}
//
////long int cm2tick(float cm) {
////  cm /= 10.0;
////  float rotates = (float)cm / (float)WheelLength;
////  return rotates * TicksInRotation;
////}
//
//
//void go(int ticks, int gL, int gR, bool sm) {
//  int counter = 1;
//  int lastState = 0;
//  Serial.println(ticks);
//  int L, R, stepL = 0, stepR = 0;
//  if (sm) {
//    L = gL / 2;
//    R = gR / 2;
//    stepL = L / 5;
//    stepR = R / 5;
//    L += 20;
//    R += 20;
//  } else {
//    L = gL;
//    R = gR;
//  }
//  Serial.println(ticks);
//  while (counter <= ticks) {
//    int cur = digitalRead(RightEncoderPin);
//    if (sm) {
//      if (total_ticks <  500 && counter % 10 == 0) {
//        L += stepL;
//        R += stepR;
//      }
//    }
//    analogWrite(LeftMotorSpeedPin, L);
//    analogWrite(RightMotorSpeedPin, R);
//    if (cur != lastState) {
//      lastState = cur;
//      counter = counter + 1;
//      total_ticks++;
//    }
//    Serial.println(total_ticks);
//  }
//}
