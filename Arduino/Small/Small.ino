typedef struct Command {
  String func;
  int param;
};

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(250);
}

void loop() {
  while (Serial.available() > 0) {
    Command cmd = readCommand();
    String F = cmd.func;
    if (F == "f") {
      forward(cmd.param);
    } else if (F == "b") {
      backward(cmd.param);
    } else if (F == "l") {
      left(cmd.param);
    } else if (F == "r") {
      right(cmd.param);
    }
  }
}
