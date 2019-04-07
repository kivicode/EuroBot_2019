int angles[5] = {0, 0, 0, 0, 0};

void setAngle(int servo_id, int angle) {
  driver.setChannelPWM(servo_id, pwmServo.pwmForAngle(angle));
}

void levelUp() {
  setAngle(0, -57);
  setAngle(2, 64);
  setAngle(5, 90);
}

void levelDown() {
  setAngle(0, 67);
  setAngle(2, -65);
  setAngle(5, -40);
}


void pompsMid() {
  setAngle(7, 55);
  setAngle(3, 3);
  setAngle(4, -40);
}

void pompsDown() {
  setAngle(7, -50);
  setAngle(3, 90);
  setAngle(4, 50);
}
