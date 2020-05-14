#ifndef MASTER
#include <Arduino.h>
#define stepPin 2
#define dirPin 3
float angle = 0;
float dif = 0;
float remainder = 0;
int length = 0;

void setup() {
  // put your setup code here, to run once:
  

  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Only do something if a new serial is available, coming from the bluetooth module
  if(Serial.available()>0){
    //dif = Serial.read();

    //Set the right direction in which the motor will rotate (depends of the connection of the coils)
    if(dif<0){
      digitalWrite(dirPin, LOW);
      //Update to new angle which is a multiple of 22.5, this is needed for the functionality with the switches
      remainder = fmod(abs(dif), 22.5);
      if(remainder>11.25) dif += remainder - 22.5;
      else dif += remainder;
    }
    else {
      digitalWrite(dirPin, HIGH);
      //Update to new angle which is a multiple of 22.5
      remainder = fmod(dif, 22.5);
      if(remainder>11.25) dif += 22.5 - remainder;
      else dif -= remainder;     
    }
    
    //Make the clock pulse with the right length
    length = 2*dif/0.9;
    //Move the motor
    for (int i = 0; i < length; i++){
      digitalWrite(stepPin, !digitalRead(stepPin));
      delayMicroseconds(500);
    }
  }
}
#endif