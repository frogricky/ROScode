#include "Motor.h"
#include "Arduino.h"
#include <Encoder.h>
#include "PD.h"


Motor::Motor(byte P, byte En, byte dirA, byte dirB, byte A, byte B) {
  PWM = P;
  Enable = En;
  directionA = dirA;
  directionB = dirB;
  enA = A;
  enB = B;
    
  motor = new Encoder(A,B);

    
  initializer();
  PDinitializer();
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
  return motor->read();
}

void Motor::Move(int in){
  if(in == 0) {
    digitalWrite(Enable,LOW);
    digitalWrite(directionA,LOW);
    digitalWrite(directionB,LOW);   
  }
  if(in <= 0) {
    digitalWrite(directionA,LOW);
    digitalWrite(directionB,HIGH);
  }
  else{
    digitalWrite(directionA,HIGH);
    digitalWrite(directionB,LOW);
  }
  digitalWrite(Enable,HIGH);

  analogWrite(PWM, abs(in));
  
}

void Motor::PDinitializer(){
  PD PD1 = PD(0, 0, 0, 0.005, 4095, 0);
  PD PD2 = PD(0, 0, 0, 0.005, 4095, 0);
  PD PD3 = PD(0, 0, 0, 0.005, 4095, 0);



}
