class Motor {
  private:
    int pinA;
    int pinB;
    int encoder;
    int state;
    int lastState;
    int counter;

  public:
    void forward() {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      state = digitalRead(encoder);
      lastState = state;
      counter = 0;
    }

    void backward() {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      state = digitalRead(encoder);
      lastState = state;
      counter = 0;
    }

    void stop() {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
    }

    bool shouldMove(int ticks) {
      if (counter < ticks) {
        state = digitalRead(encoder);
        if (state != lastState && digitalRead(encoder) != state) {
          counter++;
          lastState = state;
        }
      }
    }


    Motor(int A, int B, int encoder, bool reversed) {
      pinA = reversed ? B : A;
      pinB = reversed ? A : B;
      pinMode(A, OUTPUT);
      pinMode(B, OUTPUT);
      pinMode(encoder, OUTPUT);
    }
};

