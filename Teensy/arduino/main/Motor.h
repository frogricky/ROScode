#ifndef __Motor_H__
#define __Motor_H__

#include"Arduino.h"

class Motor{

    public:
        Motor(byte, byte, byte, byte, byte, byte);
        void initializer();
        int EncRead();
        void Move(int);
        void disattach();
        ~Motor();


    private:
        byte PWM;
        byte Enable;
        byte directionA;
        byte directionB;
        byte enA;
        byte enB;


};

#endif
