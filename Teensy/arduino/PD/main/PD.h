#ifndef __PD_H__
#define __PD_H__
#include"Arduino.h"


class PD{
  public:
    PD(double, double, double, double, double, double, bool);
    double PIDrun(double, double);
    double PIDrun2();
    
    void setvariable(double, double, double);
    double timecheck();
    
    ~PD();

  
  private:
    double setpoint = 0;
    double ProcessVariable = 0, ProcessVariableAfter = 0;
    double derivativeAction = 0;
    double kp, ki, kd;
    double dt;//0.005
    double outHIGH, outLOW;
    bool reinitialize;
    int startTime;
  
  
  
  
};

#endif
