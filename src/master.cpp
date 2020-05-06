#ifdef MASTER
#include <Arduino.h>
#include "circ-buffer.h"
#include "Wire.h"

const int MPU = 0x68;
float elapsedTime, time, timePrev;
bool err_Calculated=false;
int16_t Gyr_rawZ;
float Gyr_angle_z;
float Gyr_raw_err_z;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  
  Wire.beginTransmission(MPU);   //Begin transmission to the MPU6050
  Wire.write(0x6B);              //Write to the power management register
  Wire.write(0x00);              //
  Wire.endTransmission(true);
  
  Wire.beginTransmission(MPU);
  Wire.write(0x19);              //Write to sample rate divider register
  Wire.write(0x03);              //Change sample rate to 2kHz (because 8kHz looks a bit overkill for our application)
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x1B);              //Write to gyroscope config register
  Wire.write(0x08);              //Set full scale range to 500 degrees per second
  Wire.endTransmission(true);

  Serial.begin(9600);
  time=millis();

  //Start calculating the error with 200 samples
  if(err_Calculated==false)
  {
    for(int i=0; i<200; i++)
    {
      Wire.beginTransmission(0x68);            //begin, Send the slave adress (in this case 68) 
      Wire.write(0x47);                        //First adress of the Gyro z data
      Wire.endTransmission(false);
      Wire.requestFrom(0x68,2,true);           // Only rotation around z-axis 
         
      Gyr_rawZ=Wire.read()<<8|Wire.read();
  
      Gyr_raw_err_z = Gyr_raw_err_z + (Gyr_rawZ/65.5);  //Divide by 65.5 because datasheet says so when using a scale range of 500 degrees per second
      if(i==199)
      {
        Gyr_raw_err_z = Gyr_raw_err_z/200;
        err_Calculated=true;
      }
    }
  }  
}

void loop() {
  // put your main code here, to run repeatedly:

}
#endif