#define AIN1 7
#define AIN2 8
#define PWMA 10
#define BIN1 4
#define BIN2 2
#define PWMB 5

#include "turnout.h"

String msg;

turnout switch1 = turnout(AIN1,AIN2, PWMA);
turnout switch2 = turnout(BIN1,BIN2, PWMB);

void setup() {


  Serial.begin(9600);                       //begin serial communication with the computer
}

void loop() {

  if (Serial.available()>0) {         //if the user has entered something in the serial monitor
    msg = Serial.readString();
    
    if (msg[0] == 't') {
      if (msg[1] == '1') {
        switch1.switchDir();
      }
      if (msg[1] == '2') {
        switch2.switchDir();
      }
    }    

  }
}
