#include"Motor.h"
#include"Arduino.h"

Motor::Motor(byte pwm, byte enable, byte directionA, byte directionB, byte encoderA, byte encoderB) {
    initializer(pwm, enable, directionA, directionB, encoderA, encoderB);
}

void Motor::initialize(byte pwm, byte enable, byte directionA, byte directionB, byte encoderA, byte encoderB){
    analogWriteFrequency(pwm, 10000);
    analogWriteResolution(12);

    pinMode(pwm, OUTPUT);
    pinMode(enable, OUTPUT);
    pinMode(directionA, OUTPUT);
    pinMode(directionB, OUTPUT);
    pinMode(encoderA, INPUT);
    pinMode(encoderB, INPUT);

    analogWrite(pwm, 0);

    digitalWrite(enable,LOW);
    digitalWrite(directionA,LOW);
    digitalWrite(directionB,LOW);

}



void Motor::disattach(){
    analogWrite(pwm, 0);

    digitalWrite(enable,LOW);
    digitalWrite(directionA,LOW);
    digitalWrite(directionB,LOW);
}
