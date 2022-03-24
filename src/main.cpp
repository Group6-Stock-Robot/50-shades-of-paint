#include "Robot.h"

Robot paint50;

void setup() {
  paint50.init();
}
uint32_t missionLength = 0;
void loop() {
  if (paint50.update()) {
    missionLength = millis() - paint50.getMissionStartTimestamp();
    delay(86400000 - missionLength);
    paint50.start();
  }

}