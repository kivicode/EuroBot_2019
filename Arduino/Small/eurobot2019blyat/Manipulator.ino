void setAngle(int servo_id, int angle) {
  switch (servo_id) {
    case 0:
      servo0.write(angle);
    case 1:
       servo1.write(angle);
      break;
    case 2:
       servo2.write(angle);
      break;
    case 3:
       servo3.write(angle);
      break;
    case 4:
       servo4.write(angle);
      break;
  }
}
void test () {
}

void ostrich() {  // спрятал голову в песок work
  setAngle(1, 20);
  delay(300);
  setAngle(3, -70);

  setAngle(1, 40);
  delay(300);
  delay(300);
  setAngle(2, 30);
  delay(300);
  setAngle(3, -90);
  delay(300);
  setAngle(0, 40);
  delay(300);
  setAngle(4, -60);
  delay(300);
  setAngle(1, -30);
  delay(300);

  setAngle(0, 90);
  delay(300);
  setAngle(2, 30);
  delay(300);
}

void smeh () {   //work
  setAngle(0, 0);
  delay(500);
  setAngle(3, 80);
  delay(500);
  setAngle(4, -90);
  delay(500);
  setAngle(2, 70);
  delay(500);
  setAngle(1, -35);
  delay(500);
  setAngle(4, -90);
  delay(500);
}
