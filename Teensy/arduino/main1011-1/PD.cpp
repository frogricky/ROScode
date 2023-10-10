#include "Arduino.h"
#include "PD.h"


PD::PD(double p, double i, double d, double time, double max, double min){
  kp = p;
  ki = i;
  kd = d;
  dt = time;
  AfterP = kp;
  AfterI = ki;
  AfterD = kd;
  outHIGH = max;
  outLOW = min; 
}

double PD::PIDrun(double realtime, double target){
  startTime = millis();
  double timef = 0.0167 * timecheck();
  setpoint = target;
  ProcessVariable = realtime;
  
  if(!reinitialize || first){
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
  
  if(ki != 0){
    double error = ((setVariable + setVariableAfter) * 0.5 * (kp / ki) * timef) + integratedError;
    if(reinitialize || first || ((kp == AfterP) && (ki == AfterI) && (kd == AfterD))){

      if(((setVariable * kp) <= outHIGH) && ((setVariable * kp) >= outLOW)) {
        if(reinitialize){
          integratedError = 0;
          return OutputCheck(0.0);
        }
        else {
          integratedError = error;
          return OutputCheck(error);
        }
      }
      else{
        if ((setVariable * kp) > outHIGH) integratedError = outHIGH - (setVariable * kp);
        else integratedError = outLOW - (setVariable * kp);
      }
    }
    else{
      integratedError = AfterOUT - ((setVariable * kp) + derivativeAction);
      AfterVariable();
      return AfterOUT;
    }

  }
  else{
    return OutputCheck(0.0);    
  } 
  return 0;
}


void PD::setvariable(double p, double i, double d, bool reinit){
  
  kp = p;
  ki = i;
  kd = d;  
  reinitialize = reinit;
  
}

void PD::AfterVariable(){
  AfterP = kp;
  AfterI = ki;
  AfterD = kd;
  ProcessVariableAfter = setVariable;
  setVariableAfter = setVariable;
  first = false;
  startTime = millis();

  
}


double PD::OutputCheck(double gap){
  double PIDout = (setVariable * kp) + gap + derivativeAction;
  AfterVariable();
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


double PD::timecheck(){
  if(dt <= 0){
    if(!reinitialize){
        return (millis() - startTime) * 0.001;
    }
    else{
        return 0;
    }
  }
  else{
    return dt;
  }
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
