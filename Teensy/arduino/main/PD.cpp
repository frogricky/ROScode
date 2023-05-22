#include "Arduino.h"
#include "PD.h"


PD::PD(double p, double i, double d, double t, double outH, double outL, bool re){
  kp = p;
  ki = i;
  kd = d;
  dt = t;
  AfterP = kp;
  AfterI = ki;
  AfterD = kd;
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

  return PIDrun2(timef);
}


double PD::PIDrun2(double timef){
  setVariable = setpoint - ProcessVariable;
  
  if(!isinf(kp / ki)){
    double error = ((setVariable + setVariableAfter) * 0.5 * (kp / ki) * timef) + integratedError;
    if(reinitialize || ((kp == AfterP) && (ki == AfterI) && (kd == AfterD))){
      
      if(((setVariable * kp) <= outHIGH) && ((setVariable * kp) >= outLOW)) {
        if(reinitialize) integratedError = 0;
        else integratedError = error;
      }
      else{
        if ((setVariable * kp) > outHIGH) integratedError = outHIGH - (setVariable * kp);
        else integratedError = outLOW - (setVariable * kp);
      }
    }
    else{
      integratedError = AfterOUT - ((setVariable * kp) + derivativeAction);
      return AfterOUT;
    }


    return 0;
  }
  else{
    double PIDout = (setVariable * kp) + derivativeAction;
    if (PIDout > outHIGH){
      AfterOUT = outHIGH;
      return outHIGH;
    }
    else if (PIDout < outLOW){
      AfterOUT = outLOW;
      return outLOW;
    }
    else {
      AfterOUT = PIDout;
      return PIDout;
    }
    
  }

  AfterP = kp;
  AfterI = ki;
  AfterD = kd;
  ProcessVariableAfter = setVariable;
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
