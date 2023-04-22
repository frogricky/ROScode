#ifndef __PD_H__
#define __PD_H__
#include"Arduino.h"


class PD{
  public:
    PD(double, double, double, double, double, double, bool);
    double PIDrun(double, double);
    double PIDrun2(double);
    
    void setvariable(double, double, double);
    double timecheck();
    
    ~PD();

  
  private:
    double setpoint = 0;
    double ProcessVariable = 0, ProcessVariableAfter = 0;
    double setVariable = 0, setVariableAfter = 0;
    double derivativeAction = 0;
    double integratedError = 0;
    double kp, ki, kd, AfterP, AfterI, AfterD;
    double dt;//0.005
    double outHIGH, outLOW, AfterOUT = 0;
    bool reinitialize = true;
    int startTime;
  
  
  
  
};

#endif
