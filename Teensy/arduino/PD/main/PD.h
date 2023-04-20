#ifndef __PD_H__
#define __PD_H__
#include"Arduino.h"


class PD{
  public:
    PD(double, double, double, double, double, double, bool);
    double PIDrun();
    
    
    ~PD();

  
  private:
    double setpoint;
    double ProcessVariable;
    double kp, ki, kd;
    double dt;//0.005
    double outHIGH, outLOW;
    bool reinitialize;
    int startTime;
  
  
  
  
};

#endif
