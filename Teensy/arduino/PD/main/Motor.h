#ifndef __Motor_H__
#define __Motor_H__
#include"Arduino.h"
#include <Encoder.h>

class Motor{

  public:
    Motor(byte, byte, byte, byte, byte, byte);
    void initializer();
    int EncRead();
    void Move(int);
    void disattach();
    ~Motor();

    void PDinitializer();

  private:
    byte PWM;
    byte Enable;
    byte directionA;
    byte directionB;
    byte enA;
    byte enB;
    Encoder* motor = new Encoder(14,15);

};

#endif
