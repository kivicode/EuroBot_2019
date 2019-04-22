#include "settings.h"
#include <Movement.h>

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

  //-------------------- Езда до первых 6 шайб --------------------
  firstSix();


  // -------------------- Езда до шайб у горки --------------------
  grabNearTrap();


  //-------------------- Езда до весов --------------------
  putOnScales();

  //-------------------- Езда от весов к ускорителю --------------------
  goToSpeeder();



  //-------------------- Выгрузка шайб на ускоритель --------------------
  putOnSpeeder();

  //-------------------- Захват голдениума --------------------
  grabGoldenium();

}


void loop() {
  //  mov(10000, 0);
}
