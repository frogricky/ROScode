#ifndef __Motor_H__
#define __Motor_H__

#include"Arduino.h"

class Motor{

    public:
        Motor(byte, byte, byte, byte, byte, byte);



        void initializer();
        void disattach();
        ~Motor();


    private:
        byte pwm;
        byte enable;
        byte directionA;
        byte directionB;
        byte encoderA;
        byte encoderB;


};

#endif