int setpoint = 0;  // 初始设定为0
unsigned long i = 0;

void setup() {
  Serial.begin(9600);  // 初始化串口通信
}

void loop() {
  if()

 
  if (Serial.available()) {  // 检查串口是否有数据可读取
    String input = Serial.readStringUntil('\n');  // 读取串口数据直到换行符
    input.trim();  // 去除开头和结尾的空格
    if (input.startsWith("setpoint")) {  // 检查输入是否以 "setpoint" 开头
      String value = input.substring(9);  // 提取输入中的数值部分
      Serial.println("Received setpoint value: " + value);  // 显示接收到的 setpoint 值
    } else if (input.equals("show")) {  // 检查输入是否为 "show"
      Serial.println("Current value of setpoint: " + String(setpoint));  // 显示当前 setpoint 的值
    } else {
      int newValue = input.toInt();  // 将输入转换为整型
      // 进行后续操作，使用 newValue 进行必要的计算或控制
      setpoint = newValue;  // 更新 setpoint 的值
      Serial.println("New value received: " + String(newValue));  // 打印接收到的新值
    }
  }
  

  i++;
  delay(5);
}
