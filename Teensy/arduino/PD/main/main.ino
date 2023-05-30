#include "Arduino.h"
#include "PD.h"
#include "Motor.h"

int setpoint = 0;
double p = 0.0;
double i = 0.0;
double d = 0.0;

double previousValue = 0.0;
double variable = 0.0;

PD PIDa(p, 0, d, 0.005, 4095, -4095, true);
Motor motor2(5,21,8,6,12,11);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  processSerialInput();
  variable = PIDa.PIDrun(motor2.EncRead(), setpoint);

  if (variable != previousValue) {
    previousValue = variable; 
    Serial.println(variable, setpoint)); 
  }


  delay(5);
}






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
        PIDa.setvariable(p, i, d);
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