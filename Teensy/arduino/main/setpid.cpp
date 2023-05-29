#include "Arduino.h"
#include "Motor.h"
#include "PD.h"
#include "setpid.h"


void setpid::initializer(){
  Motor motor1(22,21,23,0,17,16);
  Motor motor2(5,21,8,6,12,11);
  Motor motor3(4,21,2,3,10,9);

  PD PD1 = PD(0, 0, 0, 0.005, 4095, 0, false);
  PD1.PIDrun(motor2.EncRead(), double setp)


}