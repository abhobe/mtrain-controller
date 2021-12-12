#include "turnout.h"
#define dirPin 12
#define pwmPin 3
#define brakePin 9
#define AIN1 7
#define AIN2 8
#define PWMA 10
#define BIN1 4
#define BIN2 2
#define PWMB 5

int sensorval;
String Speed;
int Direction;





turnout switch1 = turnout(AIN1,AIN2, PWMA);
turnout switch2 = turnout(BIN1,BIN2, PWMB);

void setup() {
  Serial.begin(9600);
  pinMode(dirPin,OUTPUT); 
  pinMode(brakePin,OUTPUT);
  //pinMode(pwmPin, OUTPUT);
  pinMode(2, INPUT);
}


bool WebMode = false;
int WebDir;

void loop() {

  if (Serial.available()) {
    String msg = Serial.readString(); 
    if (msg[0] == 'd') {
      if (msg[1] == 'f') {
        WebDir = 'f';
        digitalWrite(dirPin,HIGH); //Establish Forward Direction
        digitalWrite(brakePin,LOW); //Release the Brake
        
        Serial.println("Direction: Forwards");
      } else if (msg[1] == 'r') {
        WebDir = 'r';
        digitalWrite(dirPin,LOW); //Establishes the reverse Direction
        digitalWrite(brakePin,LOW); //Releases the Brake
        Serial.println("Direction: Reverse");
      } else if (msg[1] == 'h'){
        WebDir = 'h';
        digitalWrite(brakePin,HIGH);

        Serial.println("Direction: Halt");
      }
    }

    if (msg[0] == 's') {
      Speed = String(msg[1]) + String(msg[2]) + String(msg[3]) + String(msg[4]);
      Serial.println("Speed: " + Speed);
      analogWrite(pwmPin, Speed.toInt());      
    }

    if (msg[0] == 'q') {
      Serial.print("Direction: ");
      if (WebDir == 'f') {
        Serial.println("Forwards");
      }
      if (WebDir == 'h') {
        Serial.println("Halt");
      }
      if (WebDir == 'r') {
        Serial.println("Reverse");
      }
      Serial.println("Speed: " + Speed);
    }
    if (msg[0] == 't') {
      switch1.switchDir();
      switch2.switchDir();
      
      if (msg[1] == '1') {
        switch1.switchDir();
      }
      if (msg[1] == '2') {
        switch2.switchDir();
      }
    } 
}                                             
}
