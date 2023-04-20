
#include <PID_v2.h>

#define PIN_INPUT 0
#define PIN_OUTPUT 3

int input = 0;
double out_put = 0.0;
bool a = false;
bool b = false;



// Specify the links and initial tuning parameters
double Kp = 7, Ki = 0, Kd = 0;
PID_v2 myPID(Kp, Ki, Kd, PID::Direct);

void setup() {
  Serial.begin(9600);
  myPID.Start(analogRead(PIN_INPUT),  // input
              0,                      // current output
              100);                   // setpoint
  myPID.SetOutputLimits(0,100);
}

void loop() {
  if (Serial.available() > 0) { // 如果有数据可读取
    char c = Serial.read(); // 读取输入字符
    if (isdigit(c)) { // 如果输入字符为数字字符
      if(a){ 
        input = 0;
        a = false;
      }
      input = input * 10 + (c - '0'); // 将其转换为数字并存储到 input 变量中
      
    } else if (c == '\n') { // 如果输入字符为换行符
      Serial.print("input: "); // 输出提示信息
      Serial.println(input); // 输出输入的数字
      a = true;
    }
  }

  
  
  out_put = myPID.Run(input);
  Serial.print("out_put: "); // 输出提示信息
  Serial.println(out_put);
  Serial.print("input: "); // 输出提示信息
  Serial.println(input); // 输出输入的数字
  delay(10);
}
