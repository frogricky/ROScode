#include "Arduino.h"
#include "Motor.h"



const int delayt = 5000;

unsigned long runTime;

Motor motor1(22,21,23,0,17,16);
Motor motor2(5,21,8,6,12,11);
Motor motor3(4,21,2,3,10,9);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
  

}

void loop() {
  runTime = micros();
  
  if (Serial.available() > 0) {


    
  }
  
  Serial.println(motor1.EncRead());




 if((micros() - runTime) > delayt) Serial.println("time out");
 delay(5);
 
}
