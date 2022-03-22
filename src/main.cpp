#include <Arduino.h>
#include <Tape.h>

Tape tape(A0, A1, A2);
uint8_t buzzer = 4;
void setup() {

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  Serial.begin(9600);
  tape.init();
  uint16_t * calibration = new uint16_t[3];
  Serial.println("Place all of the robot's ir diodes over the tape and press SW3 when ready");
  while (digitalRead(13) == HIGH) {
    ;
  }
  calibration = tape.calibrateHigh();
  Serial.println("HIGH CAL");
  Serial.print("Left: ");
  Serial.println(calibration[0]);
  Serial.print("Middle: ");
  Serial.println(calibration[1]);
  Serial.print("Right: ");
  Serial.println(calibration[2]);
  delay(2000);

  Serial.println("Place all of the robot's ir diodes over the floor and press SW3 when ready");
  while (digitalRead(13) == HIGH) {
    ;
  }
  calibration = tape.calibrateLow();
  Serial.println("LOW CAL");
  Serial.print("Left: ");
  Serial.println(calibration[0]);
  Serial.print("Middle: ");
  Serial.println(calibration[1]);
  Serial.print("Right: ");
  Serial.println(calibration[2]);
  Serial.println("Calibration finished! Next you can test the operation");
}

uint8_t state;
uint8_t lastState;
int * analogue = new int[3];
int lSpeed, rSpeed;

void loop() {
  lastState = state;
  state = tape.update();
  analogue = tape.getIrAnalogue();
  lSpeed = constrain(map(analogue[1] + analogue[2], 0, 200, 0, 100), 0, 100);
  rSpeed = constrain(map(analogue[1] + analogue[0], 0, 200, 0, 100), 0, 100);
  Serial.print(tape.stateToString(state));
  Serial.print("\tl:\t");
  Serial.print(analogue[0]);
  Serial.print("\tm:\t");
  Serial.print(analogue[1]);
  Serial.print("\tr:\t");
  Serial.print(analogue[2]);
  Serial.print("\tright speed:\t");
  Serial.print(rSpeed);
  Serial.print("\tleft speed:\t");
  Serial.println(lSpeed);
  delay(100);
}