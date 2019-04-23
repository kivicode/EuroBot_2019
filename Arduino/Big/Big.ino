#include "settings.h"

int SIDE;

bool useEnemyDetection = false;
bool useStarter = false;
bool useSwitcher = false;

void setup() {
  initPins();
  initServos();
  initMovement();

  pompsDown();
  levelDown();

  waitForStart();
  setSide();

  //  setAngle(B_level, 90);
  //  pompsMid();

  //-------------------- Езда до первых 6 шайб --------------------
  //  firstSix();

  // -------------------- Езда до шайб у горки --------------------
  //    grabNearTrap();

  //-------------------- Езда до весов --------------------
  //  putOnScales();

  //-------------------- Езда от весов к ускорителю --------------------
  //  goToSpeeder();

  //-------------------- Выгрузка шайб на ускоритель --------------------
//  putOnSpeeder();

  //-------------------- Захват голдениума --------------------
//  grabGoldenium();

  //-------------------- Захват cиней шайбы на ускорителе --------------------
  grabBlue();

  //-------------------- Первозка голдениума к весам --------------------
//  goBackToScales();
}


void loop() {
  //  mov(10000, 0);
}
