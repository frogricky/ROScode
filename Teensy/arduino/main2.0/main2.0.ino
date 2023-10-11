#include "Arduino.h"
#include "Motor.h"
#include "PD.h"

/*
double p = 0.8;
double i = 0;
double d = 0.000001;
*/

const byte timeout = 13;
const int delayt = 5000;

int setpoint = 0;
double p = 0.8;
double i = 0;
double d = 0.000001;
bool SerialStop = false;

unsigned long runTime;

bool WorkingLamp = false;
int Workcont  = 0;


//(PWM, Enable, dirA, dirB, ENCA, ENCB)
Motor motor1(22,21,23,0,16,17);
Motor motor2(5,21,8,6,11,12);
Motor motor3(4,21,2,3,9,10);
//(double p, double i, double d, double time, double max, double min)
PD motorPD1(p,i,d,delayt/1000,4095,-4095);
PD motorPD2(p,i,d,delayt/1000,4095,-4095);
PD motorPD3(p,i,d,delayt/1000,4095,-4095);

PD testPD(p,i,d,delayt/1000,4095,-4095);


void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");

  pinMode(timeout, OUTPUT);
}


void loop() {
  runTime = micros();
  processSerialInput();
  
  





 Working();
 if((micros() - runTime) > delayt) digitalWrite(timeout,HIGH);
 delay(5);
}









void PIDTEST(){
  testPD.setvariable(p, i, d, SerialStop);
  int test = testPD.PIDrun(5000, setpoint);
  Serial.println(test);
  Serial.println(setpoint);
}





void exPIDmotor(){
  motorPD2.setvariable(p, i, d, SerialStop);
  motor2.Move(motorPD2.PIDrun(motor2.EncRead(), setpoint));
  char outStr[20];
  dtostrf(p, 10, 7, outStr); Serial.print("P: "); Serial.print(outStr);
  dtostrf(i, 10, 7, outStr); Serial.print("  I: "); Serial.print(outStr);
  dtostrf(d, 10, 7, outStr); Serial.print("  D: "); Serial.println(outStr);
  Serial.println(motor2.EncRead());
  Serial.println(setpoint);
}





//-------------------------------------------------------------------------------
//------------ex motor 
void exmotor() {
  motor1.Move(100);
  Serial.println(motor1.EncRead());
}
//------------ex motor


//-------------------------------------------------------------------------------
//---------------工作燈
void Working(){
  Workcont++;

  if ((Workcont % 200) == 0){
    if(WorkingLamp == false) WorkingLamp = true;
    else WorkingLamp = false;
    digitalWrite(timeout,WorkingLamp);
  } 
}
//---------------工作燈
//-------------------------------------------------------------------------------


//-----------修改變數
void processSerialInput() {

  // 檢查是否有新的Serial數據
  if (Serial.available()) {
    char buffer[50]; // 假設輸入的最大長度為50個字元
    memset(buffer, 0, sizeof(buffer)); // 清空緩存

    int length = Serial.readBytesUntil('\n', buffer, sizeof(buffer) - 1);

    if (length > 0) {
      buffer[length] = '\0'; // 添加終止字元

      double tempP, tempI, tempD;
      int tempSetpoint;
      int tempStop;

      // 使用sscanf解析數據
      int parsed = sscanf(buffer, "%lf %lf %lf %d %d", &tempP, &tempI, &tempD, &tempSetpoint, &tempStop);

      if (parsed == 5) {  // 如果成功解析了5個變數
        p = tempP;
        i = tempI;
        d = tempD;
        setpoint = tempSetpoint;
        SerialStop = static_cast<bool>(tempStop);

        char outStr[20]; // 為dtostrf函數的輸出創建緩存

        Serial.println("Data received successfully:");
        dtostrf(p, 10, 7, outStr); Serial.print("P: "); Serial.println(outStr);
        dtostrf(i, 10, 7, outStr); Serial.print("I: "); Serial.println(outStr);
        dtostrf(d, 10, 7, outStr); Serial.print("D: "); Serial.println(outStr);
        Serial.print("Setpoint: "); Serial.println(setpoint);
        Serial.print("Stop: "); Serial.println(SerialStop);
      } else {
        Serial.println("Failed to parse data. Please re-enter.");
        Serial.print("P: "); Serial.println(p);
        Serial.print("I: "); Serial.println(i);
        Serial.print("D: "); Serial.println(d);
        Serial.print("Setpoint: "); Serial.println(setpoint);
        Serial.print("Stop: "); Serial.println(SerialStop);
      }
    }
  }
}
//-----------修改變數
