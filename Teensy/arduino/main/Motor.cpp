#include "Motor.h"
#include "Arduino.h"
#include <Encoder.h>
#include <PID_v2.h>



Motor::Motor(byte P, byte En, byte dirA, byte dirB, byte A, byte B) {
    PWM = P;
    Enable = En;
    directionA = dirA;
    directionB = dirB;
    enA = A;
    enB = B;
    
    initializer();
}

Motor::~Motor(){
    disattach();
}

void Motor::initializer(){

    analogWriteFrequency(PWM, 10000);
    analogWriteResolution(12);

    pinMode(PWM, OUTPUT);
    pinMode(Enable, OUTPUT);
    pinMode(directionA, OUTPUT);
    pinMode(directionB, OUTPUT);
    

    analogWrite(PWM, 0);

    digitalWrite(Enable,LOW);
    digitalWrite(directionA,LOW);
    digitalWrite(directionB,LOW);


}

void Motor::disattach(){
    analogWrite(PWM, 0);

    digitalWrite(Enable,LOW);
    digitalWrite(directionA,LOW);
    digitalWrite(directionB,LOW);
}


int Motor::EncRead(){
  Encoder motor(enA,enB);
  
  return motor.read();
}

void Motor::Move(int in){
  analogWrite(PWM, in);
  
}
