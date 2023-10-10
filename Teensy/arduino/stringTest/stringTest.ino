
int setpoint = 0;
double p = 0;
double i = 0;
double d = 0;
bool stop = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);



}

void loop() {
  // put your main code here, to run repeatedly:
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