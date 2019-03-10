Motor LM = Motor(LeftMotorForwardPin, LeftMotorBackwardPin, LeftMotorSpeedPin, LeftEncoderPin, false);
Motor RM = Motor(RightMotorForwardPin, RightMotorBackwardPin, RightMotorSpeedPin, RightEncoderPin, true);

void forward(int cm) {
  LM.forward();
  RM.forward();
  //  int start = millis();
  while (LM.getPassed() < cm && RM.getPassed() < cm) {
    Serial.println(LM.getPassed());
  }
  //  delay(1000);
  LM.stop();
  RM.stop();
  LM.backward();
  RM.backward();
  delay(100);
  LM.stop();
  RM.stop();
  //  RM.stop();
}

//void backward(int cm) {
//  LM.backward();
//  RM.backward();
//  go(cm);
//}
//
//void left(int deg) {
//
//}
//
//void right(int deg) {
//
//}
//
//long int cm2ticks(int cm) {
//  int mm = cm * 10;
//  long int ticks = (mm / WheelLength) * TicksInRotation;
//  return ticks;
//}
//
//void go(int cm) {
//  long int ticks = cm2ticks(cm);
//  while (LM.shouldMove(ticks) || RM.shouldMove(ticks)) {}
//  LM.stop();
//  RM.stop();
//}
//

