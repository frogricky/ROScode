int* input = 0; //宣告名為"input"的變數
int* setpoint = 0;
double p = 0;
double i = 0;
double d = 0;

bool isInput = false;
bool issetpoint = false;
bool isp = false;
bool isi = false;
bool isd = false; //當接收到"input"時設為true



class handle{
  public:
    void Hinput(int);
    
  
  private:
    char input[5] = "input";
  
};

void handle::Hinput(int input){

  
  
}





void setup() {
  Serial.begin(9600); //開啟Serial通訊，設定傳輸速率為9600 bits/s
}

void handleInput() {
  if (Serial.available() > 0) { //如果Serial有可用的資料
    String inputStr = Serial.readString(); //讀取輸入的字串
    inputStr.trim(); //清除字串開頭和結尾的空白字元

    if (inputStr == "input") { //如果輸入的字串為"input"
      isInput = true; //設置旗標為true
      Serial.println("Please enter a new input value:"); //提示用戶輸入新的input值
    }
    else if (isInput) { //如果旗標為true
      input = inputStr.toInt(); //將輸入的字串轉換為整數並存入input變數
      Serial.print("input set to: "); //顯示訊息
      Serial.println(*input); //顯示input變數的值
      isInput = false; //重置旗標
    }
  

    if (inputStr == "input") { //如果輸入的字串為"input"
      isInput = true; //設置旗標為true
      Serial.println("Please enter a new input value:"); //提示用戶輸入新的input值
    }
    else if (isInput) { //如果旗標為true
      input = inputStr.toInt(); //將輸入的字串轉換為整數並存入input變數
      Serial.print("input set to: "); //顯示訊息
      Serial.println(*input); //顯示input變數的值
      isInput = false; //重置旗標
    }


    
  }
}

void printInput() {
  //如果input變數被修改，顯示新的值
  static int old_input = 0; //宣告名為"old_input"的靜態變數，用於儲存上一次的input值
  if (input != old_input) { //如果input值有變動
    Serial.print("input: "); //顯示訊息
    Serial.println(*input); //顯示input變數的值
    old_input = input; //更新old_input變數的值
  }
}

void loop() {
  handleInput();
  printInput();
}
