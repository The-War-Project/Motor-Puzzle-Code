#ifndef MASTER
#include <Arduino.h>
#include <math.h>

#define stepPin 2
#define dirPin 3
#define sw1 4
#define sw2 5
#define sw3 6
#define sw4 7
#define ledPin 8
float angle = 0;
float dif = 0;
float remainder = 0;
int length = 0;
int switcher=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  pinMode(sw4, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, LOW);
  digitalWrite(ledPin, LOW);
}

void loop() {
  //Only do something if a new serial is available, coming from the bluetooth module
  if(Serial.available()>0){
    dif = Serial.read();
    angle += round(dif/22.5)*22.5;

    //Angle interval must be between 180 & -180
    if(angle>180) angle -= 360;
    else if(angle<=-180) angle += 360; 

    //Set the right direction in which the motor will rotate (depends of the connection of the coils)
    if(dif<0){
      digitalWrite(dirPin, LOW);
    }
    else {
      digitalWrite(dirPin, HIGH);  
    }
    
    //Make the clock pulse with the right length
    length = 50*round(dif/22.5);
    //Move the motor
    for (int i = 0; i < length; i++){
      digitalWrite(stepPin, !digitalRead(stepPin));
      delayMicroseconds(500);
    }
  }
  //Check if led must be turned on in this setting
  switcher = angle/22.5;
    switch(switcher){
      case 0:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case 1:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case 2:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case 3:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case 4:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case 5:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case 6:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case 7:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case 8:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case -1:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case -2:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case -3:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case -4:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case -5:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case -6:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      case -7:
        if(digitalRead(sw1)==0&&digitalRead(sw2)==0&&digitalRead(sw3)==0&&digitalRead(sw4==0)) digitalWrite(ledPin,HIGH);
        else digitalWrite(ledPin, LOW);
        break;
      default:
        digitalWrite(ledPin, HIGH); 
        Serial.write("De hoek is geen veelvoud van 22.5");
    }
}
#endif