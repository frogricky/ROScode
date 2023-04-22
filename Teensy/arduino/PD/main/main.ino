#include "Arduino.h"
#include "PD.h"

PD PIDa(1.0, 0, 0, 0.005, 100, -100, true);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(PIDa.PIDrun(-70, -100));

  delay(5);
}
