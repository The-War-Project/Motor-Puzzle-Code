#include <Arduino.h>
#define MS1Pin 2
#define MS2Pin 3
#define MS3Pin 4
#define stepPin 5
#define dirPin 6

void setup() {
  // put your setup code here, to run once:
  pinMode(MS1Pin, OUTPUT);
  pinMode(MS2Pin, OUTPUT);
  pinMode(MS3Pin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  digitalWrite(MS1Pin, LOW);
  digitalWrite(MS2Pin, HIGH);
  digitalWrite(MS3Pin, LOW);
  digitalWrite(dirPin, HIGH);
  digitalWrite(stepPin, LOW);
  delay(200);
  digitalWrite(stepPin, HIGH);
}

void loop() {

}