#include "Arduino.h"
#include "Motor.h"
#include "PD.h"

const byte timeout = 13;
const int delayt = 5000;

int setpoint = 0;
double p = 0;
double i = 0;
double d = 0;

unsigned long runTime;
//(PWM, Enable, dirA, dirB, ENCA, ENCB)
Motor motor1(22,21,23,0,17,16);
Motor motor2(5,21,8,6,12,11);
Motor motor3(4,21,2,3,10,9);
//(double p, double i, double d, double time, double max, double min)
PD motorPD1(p,i,d,delayt/1000,4095,-4095);
PD motorPD2(p,i,d,delayt/1000,4095,-4095);
PD motorPD3(p,i,d,delayt/1000,4095,-4095);



void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");

  pinMode(timeout, OUTPUT);
}


void loop() {
  runTime = micros();
  processSerialInput();
  

  
  exPIDmotor();


 if((micros() - runTime) > delayt) digitalWrite(timeout,HIGH);
 delay(5);
 
}








void exPIDmotor(){
  motorPD1.setvariable(p, i, d, false)
  motor1.Move(motorPD1.PIDrun(motor1.EncRead(), 100));

}




//------------ex motor 
void exmotor() {
  motor1.Move(100);
  Serial.println(motor1.EncRead());
}
//------------ex motor

















//-----------修改變數
void processSerialInput() {
  if(Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if(input == "show") {
      showValues();
    } else {
      if(input.indexOf(" ") > 0) {
        updateValue(input);
      }
    }
  }
}

void showValues() {
  Serial.println("setpoint: " + String(setpoint));
  Serial.println("p: " + String(p, 7));
  Serial.println("i: " + String(i, 7));
  Serial.println("d: " + String(d, 7));
}

void updateValue(String input) {
  String varName = input.substring(0, input.indexOf(" "));
  String varValue = input.substring(input.indexOf(" ") + 1);

  if(varName == "setpoint") {
    setpoint = varValue.toInt();
  } else if(varName == "p") {
    p = varValue.toFloat();
  } else if(varName == "i") {
    i = varValue.toFloat();
  } else if(varName == "d") {
    d = varValue.toFloat();
  }
}
//-----------修改變數
