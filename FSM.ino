/*
   FSM assignment
*/

#include <Arduino.h>
#include <Wire.h>

//global bool for direction
bool reversed = false;

//enum that makes the states
enum State{
  s0 = 0, sRev0 = 0,
  s1 = 1, sRev1 = 1,
  s2 = 2, sRev2 = 2,
  s3 = 3, sRev3 = 3,
  s4 = 4, sRev4 = 4,
  s5 = 5, sRev5 = 5,
  s6 = 6, sRev6 = 6,
  s7 = 7, sRev7 = 7
} fsmState = s7;     //start at s7 so that the first one displayed is s0

void setup() {
  Serial.begin(9600);
}

void loop() {
  //if there's keyboard input, swap reversed
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    if (inByte == 114) checkReverse();
  }

  //choose next state
  fsmState = determineNextState(fsmState);

  //print based on state
  if (fsmState == s0 || fsmState == sRev0) Serial.println("0 :  000");
  else if (fsmState == s1 || fsmState == sRev1) Serial.println("1 :  001");
  else if (fsmState == s2 || fsmState == sRev2) Serial.println("2 :  010");
  else if (fsmState == s3 || fsmState == sRev3) Serial.println("3 :  011");
  else if (fsmState == s4 || fsmState == sRev4) Serial.println("4 :  100");
  else if (fsmState == s5 || fsmState == sRev5) Serial.println("5 :  101");
  else if (fsmState == s6 || fsmState == sRev6) Serial.println("6 :  110");
  else Serial.println("7 :  111");

  //1 second intervals to make the readout manageable
  delay(1000);
}

//choose next state
State determineNextState(State currentState){
   int value = (int)(currentState);

   //choose based on current state's value, not current state itself
   //This streamlines the process of reversing
   if (reversed){
    if (value == 0) return sRev7;
    else if (value == 1) return sRev0;
    else if (value == 2) return sRev1;
    else if (value == 3) return sRev2;
    else if (value == 4) return sRev3;
    else if (value == 5) return sRev4;
    else if (value == 6) return sRev5;
    else return sRev6;
   } else {
    if (value == 0) return s1;
    else if (value == 1) return s2;
    else if (value == 2) return s3;
    else if (value == 3) return s4;
    else if (value == 4) return s5;
    else if (value == 5) return s6;
    else if (value == 6) return s7;
    else return s0;
   }
}

//just swap reversed bool and print that it's reversing
bool checkReverse(){
  Serial.println("--Reverse--");
  reversed = !reversed;
}
