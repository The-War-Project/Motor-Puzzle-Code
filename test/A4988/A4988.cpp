#include <Arduino.h>
#define stepPin 2 //D2
#define dirPin 3  //D3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, LOW);
  for (int i = 0; i < 800; i++){
      digitalWrite(stepPin, !digitalRead(stepPin));
      delayMicroseconds(500);
 }
}

void loop() {}