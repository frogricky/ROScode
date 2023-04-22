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

double PD::PIDrun(double variable, double setp){
  double timef = 0.0167 * timecheck();
  setpoint = setp;
  ProcessVariable = variable;
  
  if(!reinitialize){
    if(timef > 0){
      derivativeAction = ((((ProcessVariable - ProcessVariableAfter) * -1) * (kd * kp)) / timef);

      ProcessVariableAfter = ProcessVariable;
    }
  }  
  else{
    ProcessVariableAfter = ProcessVariable;
    derivativeAction = 0;
  } 

  return PIDrun2();
}


double PD::PIDrun2(){
  
  
  if(!isinf(kp / ki)){




    return 0;
  }
  else{
    double PIDout = ((setpoint - ProcessVariable) * kp) + derivativeAction;
    if (PIDout > outHIGH) return outHIGH;
    else if (PIDout < outLOW) return outLOW;
    else return PIDout;
    
  }

  
}


void PD::setvariable(double p, double i, double d){
  kp = p;
  ki = i;
  kd = d;  
}



double PD::timecheck(){
  if(dt <= 0){
    return (millis() - startTime) * 0.001;
  }
  else{
    return dt;
  }

  startTime = millis();
}



PD::~PD(){   
  reinitialize = true;
  setpoint = 0;
  ProcessVariable = 0;
  ProcessVariableAfter = 0;
  derivativeAction = 0;
  kp = 0;
  ki = 0;
  kd = 0;
  
}
