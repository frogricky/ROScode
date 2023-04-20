#include "Arduino.h"
#include "PD.h"


PD::PD(double p, double i, double d, double t, double outH, double outL, bool re){
  kp = p;
  ki = i;
  kd = d;
  dt = t;
  outHIGH = outH;
  outLOW = outL; 
  reinitialize = re;
  startTime = millis();
}

double PD::PIDrun(){
  if(!reinitialize){
    if((0.0167 * (millis() - startTime)) > 0){


      
    }
    
    
    
  }  
}


PD::~PD(){   
  
}
