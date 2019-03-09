Motor* LM = new Motor(LeftMotorPinA, LeftMotorPinB, LeftEncoderPin, false);
Motor* RM = new Motor(RightMotorPinA, RightMotorPinB, LeftEncoderPin, true);

void forward(int cm) {
  LM->forward();
  RM->forward();
  go();
}

void backward(int cm) {
  LM->backward();
  RM->backward();
  go();
}

void left(int deg) {

}

void right(int deg) {

}

long int cm2ticks(int cm) {
  int mm = cm * 10;
  long int ticks = (mm / WheelLength) * TicksInRotation;
  return ticks;
}

void go() {
  long int ticks = cm2ticks(cm);
  while (LM->shouldMove(ticks) || RM->shouldMove(ticks)) {}
  LM->stop();
  RM->stop();
}
}

