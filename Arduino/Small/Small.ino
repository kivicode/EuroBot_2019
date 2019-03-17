
#define Speed 100 // процентов
#define LeftMotorBackwardPin 4
#define LeftMotorForwardPin 3
#define LeftMotorSpeedPin 2

#define LeftEncoderPin 5


#define RightMotorBackwardPin 9
#define RightMotorForwardPin 8
#define RightMotorSpeedPin 7

#define RightEncoderPin 6
/* TODO: Test me */
typedef struct Command {
  String func;
  int param;
};

void setup() {
  Serial.begin(9600);
  pinMode(LeftMotorForwardPin, OUTPUT);
  pinMode(LeftMotorBackwardPin, OUTPUT);

  pinMode(RightMotorForwardPin, OUTPUT);
  pinMode(RightMotorBackwardPin, OUTPUT);

  pinMode(LeftMotorSpeedPin, OUTPUT);
  pinMode(RightMotorSpeedPin, OUTPUT);

  pinMode(LeftEncoderPin, INPUT_PULLUP);
  pinMode(RightEncoderPin, INPUT_PULLUP);


  Serial.setTimeout(150);
}


String SUCC = "~";

void loop() {
  while (Serial.available() > 0) {
    String in = String(Serial.readString());
    if (in != "") {
      String cmd = split(in, '(', 0);
      String params = split(split(in, '(', 1), ')', 0);
      if (cmd == "cf") {
        forward(2);
        Serial.print(SUCC);
      }
      else if (cmd == "cb") {
        backward(2);
        Serial.print(SUCC);
      }
      else if (cmd == "cl") {
        left(1);
        Serial.print(SUCC);
      }
      else if (cmd == "cr") {
        right(1);
        Serial.print(SUCC);
      }
    }
  }
}
