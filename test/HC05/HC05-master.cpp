#ifdef MASTER
#include <Arduino.h>
bool foo = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(foo==true){
  Serial.print('1');
  }
  else Serial.print('0');
  foo=!foo;
  delay(1000);
}
#endif