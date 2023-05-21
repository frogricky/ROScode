int setpoint = 0;
float p = 0;
float i = 0;
float d = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  processSerialInput();
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
