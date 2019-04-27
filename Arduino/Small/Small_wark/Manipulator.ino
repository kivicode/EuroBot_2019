//void setAngle_(int servo_id, int angle) {
//  driver.setChannelPWM(servo_id, pwmServo.pwmForAngle(angle));
//}
//
//void setAngle(int servo_id, int angle, int del) {
//  if (del == 0) {
//    setAngle_(servo_id, angle);
//    angles[servo_id] = angle;
//    return;
//  }
//
//  int prev = angles[servo_id];
//  int curr = angle;
//
//  if (prev < curr) {
//    for (int a = prev; a <= curr; ++a) {
//      setAngle_(servo_id, a);
//      delay(del);
//    }
//  } else {
//    for (int a = prev; a > curr; --a) {
//      setAngle_(servo_id, a);
//      delay(del);
//    }
//  }
//
//  angles[servo_id] = curr;
////}
//void setAngle(int servo_id, int angle) {
//  //  setAngle(servo_id, -angle, 0);
//  //  angles[servo_id] = angle;
//  switch (servo_id) {
//    case 0:
//      servo0.write(angle);
//    case 1:
//       servo1.write(angle);
//      break;
//    case 2:
//       servo2.write(angle);
//      break;
//    case 3:
//       servo3.write(angle);
//      break;
//    case 4:
//       servo4.write(angle);
//      break;
//  }
//}
//void test () {
//
//  //  takeRU();
//  //  delay(2000);
//  //
//  //  takeRD();
//  //  delay(2000);
//  //
//  //  takeLD();
//  //  delay(2000);
//  //
//  //  delay(3000);
//  //  delay(200000);
//}
//
//void straight() {
//  setAngle(0, 0);
//  delay(300);
//  setAngle(1, 90);
//  delay(300);
//
//  setAngle(2, 40);
//  delay(300);
//
//  setAngle(4, 20);
//  delay(300);
//  setAngle(1, -20);
//  delay(300);
//  setAngle(3, 40);
//  delay(300);
//
//  if (digitalRead(storona) == 0) {
//    setAngle(0, 90);
//    delay(200);
//  } else {
//    setAngle(0, -90);
//    delay(200);
//  }
//}

void enablePomp() {
  digitalWrite(pomp, LOW);
  digitalWrite(otpusk, HIGH);
}

void disablePomp() {
  digitalWrite(pomp, HIGH);
  digitalWrite(otpusk, HIGH);
}

void kick () {
  digitalWrite(pomp, HIGH);
  digitalWrite(otpusk, LOW);
}

//void ostrich() {  // спрятал голову в песок work
//  setAngle(1, 20);
//  delay(300);
//  setAngle(3, -70);
//
//  setAngle(1, 40);
//  delay(300);
//  delay(300);
//  setAngle(2, 30);
//  delay(300);
//  setAngle(3, -90);
//  delay(300);
//  setAngle(0, 40);
//  delay(300);
//  setAngle(4, -60);
//  delay(300);
//  setAngle(1, -30);
//  delay(300);
//
//  setAngle(0, 90);
//  delay(300);
//  setAngle(2, 30);
//  delay(300);
//}
//
//void smeh () {   //work
//  setAngle(0, 0);
//  delay(500);
//  setAngle(3, 80);
//  delay(500);
//  setAngle(4, -90);
//  delay(500);
//  setAngle(2, 70);
//  delay(500);
//  setAngle(1, -35);
//  delay(500);
//  setAngle(4, -90);
//  delay(500);
//}
//
//
//void grab() { //work
//  enablePomp(); //!!
//  delay(300);
//  setAngle(2, 90);
//  delay(300);
//  setAngle(0, 0);
//  delay(300);
//  setAngle(1, -28);
//  delay(300);
//  setAngle(2, 90);
//  delay(300);
//  setAngle(3, 38);
//  delay(300);
//  setAngle(2, 38);
//  delay(300);
//  setAngle(4, 20);
//  delay(300);
//  setAngle(1, 8);
//  delay(4000);
//}
//
//void midPos() { //work
//  enablePomp(); //!!
//  setAngle(0, 0);
//  delay(300);
//  enablePomp();
//  setAngle(1, -40);
//  delay(300);
//  enablePomp();
//  setAngle(4, -85);
//  delay(300);
//  setAngle(2, 90);
//  delay(300);
//  enablePomp();
//  setAngle(3, 40);
//  delay(300);
//  enablePomp();
//
//  enablePomp();
//  setAngle(3, -60);
//  delay(300);
//  enablePomp();
//  setAngle(1, 40);
//  delay(300);
//  enablePomp();
//  setAngle(2, -40);
//  delay(300);
//  enablePomp();
//  setAngle(1, 60);
//  delay(300);
//  enablePomp();
//  setAngle(4, -10);
//  delay(300);
//  enablePomp();
//  setAngle(3, -90);
//  delay(300);
//  enablePomp(); //!!
//  delay(300);
//  enablePomp();
//}
//
//void takeUp() {
//  setAngle(2, -40);
//  setAngle(4, -10);
//  setAngle(3, -90);
//
//  setAngle(1, 25);
//  delay(300);
//  //     setAngle(2, -45);
//  //    delay(2000);
//  setAngle(4, -20);
//  delay(300);
//  setAngle(2, -60);
//  delay(300);
//  setAngle(3, -30);
//  delay(300);
//  setAngle(1, 5);
//  delay(300);
//
//}
//
//void takeDown() {
//  setAngle(2, -40);
//  setAngle(4, -10);
//  setAngle(3, -90);
//
//  setAngle(1, 25);
//  delay(300);
//  setAngle(2, -70);
//  delay(300);
//  setAngle(3, -55);
//  delay(300);
//  setAngle(4, -20);
//  delay(300);
//}
//
//
//void takeLU() {
//  enablePomp(); //!!
//  grab();
//  enablePomp();//!
//  midPos();
//  enablePomp();//!!
//  setAngle(0, 30);
//  enablePomp();///!!
//  takeUp();
//  enablePomp();//!!
//  delay(1000);
//  kick();
//  disablePomp();
//  delay(1000);
//  ostrich();
//}
//
//void takeRU() {
//  enablePomp(); //!!
//  grab();
//  enablePomp();//!
//  midPos();
//  enablePomp();//!!
//  setAngle(0, -30);
//  enablePomp();///!!
//  takeUp();
//  enablePomp();//!!
//  delay(1000);
//  kick();
//  disablePomp();
//  delay(1000);
//  ostrich();
//}
//
//void takeRD() {
//  enablePomp(); //!!
//  grab();
//  enablePomp();//!
//  midPos();
//  enablePomp();//!!
//  setAngle(0, -30);
//  enablePomp();///!!
//  takeDown();
//  enablePomp();//!!
//  delay(1000);
//  kick();
//  disablePomp();
//  delay(1000);
//  ostrich();
//}
//
//void takeLD() {
//  enablePomp(); //!!
//  grab();
//  enablePomp();//!
//  midPos();
//  enablePomp();//!!
//  setAngle(0, 30);
//  enablePomp();///!!
//  takeDown();
//  enablePomp();//!!
//  delay(1000);
//  kick();
//  disablePomp();
//  delay(1000);
//  ostrich();
//}
//
//int takeNumber = 0;
//
//void putRU() {
//  ostrich();
//  midPos();
//  enablePomp();
//  delay(1000);
//  setAngle(0, -20);
//  takeUp();
//  enablePomp();
//  setAngle(4, -45);
//  delay(300);
//  setAngle(2, -50);
//  delay(300);
//  setAngle(1, -30);
//  delay(300);
//  enablePomp();
//  delay(3000);
//  ostrich();
//  straight();
//  kick();
//  delay(1000);
//  disablePomp();
//}
//void putLU() {
//  ostrich();
//  midPos();
//  enablePomp();
//  delay(1000);
//  setAngle(0, 20);
//  takeUp();
//  enablePomp();
//  setAngle(4, -45);
//  delay(300);
//  setAngle(2, -50);
//  delay(300);
//  setAngle(1, -30);
//  delay(300);
//  enablePomp();
//  delay(3000);
//  ostrich();
//  straight();
//  kick();
//  delay(1000);
//  disablePomp();
//}
//void putRD() {
//  ostrich();
//  midPos();
//  enablePomp();
//  delay(1000);
//  setAngle(0, -20);
//  takeDown();
//  enablePomp();
//  setAngle(4, -45);
//  delay(300);
//  setAngle(2, -50);
//  delay(300);
//  setAngle(1, -30);
//  delay(300);
//  enablePomp();
//  delay(3000);
//  ostrich();
//  straight();
//  kick();
//  delay(1000);
//  disablePomp();
//}
//void putLD() {
//  ostrich();
//  midPos();
//  enablePomp();
//  delay(1000);
//  setAngle(0, 20);
//  takeDown();
//  enablePomp();
//  setAngle(4, -45);
//  delay(300);
//  setAngle(2, -50);
//  delay(300);
//  setAngle(1, -30);
//  delay(300);
//  enablePomp();
//  delay(3000);
//  ostrich();
//  straight();
//  kick();
//  delay(1000);
//  disablePomp();
//}
//int takeNumbe = 0;
//int putNumber = 0;
//void take( int kuda) {
//  switch (kuda) {
//    case 3:
//      takeRU();
//      break;
//    case 1:
//      takeLU();
//      break;
//    case 2:
//      takeLD();
//      break;
//    case 0:
//      takeRD();
//      break;
//  }
//  takeNumber++;
//}
//void putt(int kuda) {
//  switch (kuda) {
//    case 3:
//      putRU();
//      break;
//    case 1:
//      putLU();
//      break;
//    case 2:
//      putLD();
//      break;
//    case 0:
//      putRD();
//      break;
//  }
//  putNumber++;
//}
