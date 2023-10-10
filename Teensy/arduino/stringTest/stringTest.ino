// 定義變數
double p = 0.0;
double i = 0.0;
double d = 0.0;
int setpoint = 0;
bool stop = false;

const byte timeout = 13;

bool WorkingLamp = false;
int Workcont  = 0;

void setup() {
  // 開始Serial通訊
  Serial.begin(9600);
  Serial.println("Ready to receive data:");
  pinMode(timeout, OUTPUT);
}

void loop() {
  Workcont++;

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
        stop = static_cast<bool>(tempStop);

        char outStr[20]; // 為dtostrf函數的輸出創建緩存

        Serial.println("Data received successfully:");
        dtostrf(p, 10, 7, outStr); Serial.print("P: "); Serial.println(outStr);
        dtostrf(i, 10, 7, outStr); Serial.print("I: "); Serial.println(outStr);
        dtostrf(d, 10, 7, outStr); Serial.print("D: "); Serial.println(outStr);
        Serial.print("Setpoint: "); Serial.println(setpoint);
        Serial.print("Stop: "); Serial.println(stop);
      } else {
        Serial.println("Failed to parse data. Please re-enter.");
        Serial.print("P: "); Serial.println(p);
        Serial.print("I: "); Serial.println(i);
        Serial.print("D: "); Serial.println(d);
        Serial.print("Setpoint: "); Serial.println(setpoint);
        Serial.print("Stop: "); Serial.println(stop);
      }
    }
  }
  // 您的其他代碼...
  if ((Workcont % 200) == 0){
    if(WorkingLamp == false) WorkingLamp = true;
    else WorkingLamp = false;
    digitalWrite(timeout,WorkingLamp);
  } 

  delay(5);
}
