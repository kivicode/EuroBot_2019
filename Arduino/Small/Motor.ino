#define TicksInRotation 216
#define WheelRadiusMM 38.5
#define WheelLength WheelRadiusMM * PI

class Motor {
  private:
    int pinF;
    int pinB;
    int pinS;
    int encoder;
    int state;
    int lastState;
    int counter = 0;

  public:
    void forward() {
      analogWrite(pinS, 80);
      digitalWrite(pinB, LOW);
      digitalWrite(pinF, HIGH);
      counter = 0;
    }

    void backward() {
      analogWrite(pinS, 127);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinF, LOW);
      counter = 0;
    }

    void stop() {
      digitalWrite(pinF, LOW);
      digitalWrite(pinB, LOW);
      counter = 0;
    }

    int getPassed() {
      state = digitalRead(encoder);
      if (lastState != state) {
        lastState = state;
        counter++;
      }
      return ((float)counter / TicksInRotation) * WheelLength / 20;
    }

    Motor(int F, int B, int S, int E, bool reversed) {
      pinF = reversed ? B : F;
      pinB = reversed ? F : B;
      pinS = S;
      encoder = E;

      pinMode(F, OUTPUT);
      pinMode(B, OUTPUT);
      pinMode(S, OUTPUT);
      pinMode(encoder, INPUT_PULLUP);
    }
};

