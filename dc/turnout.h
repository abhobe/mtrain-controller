class turnout {
    public:
        turnout(const int inA, const int inB, const int pwm);
        String state;
        void switchDir();
    private:
        int _inA;
        int _inB;
        int _pwm;
};

turnout::turnout(int inA, int inB, int pwm) {
    pinMode(inA, OUTPUT);
    pinMode(inB, OUTPUT);
    pinMode(pwm, OUTPUT);

    _inA = inA;
    _inB = inB;
    _pwm = pwm;
    state = "s";
    Serial.println("Created");
}

void turnout::switchDir() {
    if (state == "s")                                 //if the motor should drive forward (positive speed)
    {
      digitalWrite(_inA, HIGH);                         //set pin 1 to high
      digitalWrite(_inB, LOW);                          //set pin 2 to low
   
      state = "t";
      Serial.println("Switched: Turned");
     }
    else if (state == "t")                            //if the motor should drive backward (negative speed)
    {
        digitalWrite(_inA, LOW);                          //set pin 1 to low
        digitalWrite(_inB, HIGH);                         //set pin 2 to high
        state = "s";
        Serial.println("Switched: Straight");
    }
    else                                                //if the motor should stop
    {
        digitalWrite(_inA, LOW);                          //set pin 1 to low
        digitalWrite(_inB, LOW);                          //set pin 2 to low
    }
    analogWrite(_pwm, 255);                 //now that the motor direction is set, drive it at the entered speed
    delay(250);
    analogWrite(_pwm, 0);
    digitalWrite(_inA, LOW);                          //set pin 1 to low
    digitalWrite(_inB, LOW);                          //set pin 2 to low
}