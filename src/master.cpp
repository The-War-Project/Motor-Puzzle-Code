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
CircBuffer values;
float oldAngle, newAngle, angleShift, avg;

void setup() {
  //MPU6050 init
  Wire.begin();
  
  Wire.beginTransmission(MPU);   //Begin transmission to the MPU6050
  Wire.write(0x6B);              //Write to the power management register
  Wire.write(0x00);              //Reset
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
      Wire.requestFrom(MPU,2,true);           // Only rotation around z-axis 
         
      Gyr_rawZ=Wire.read()<<8|Wire.read();
  
      Gyr_raw_err_z = Gyr_raw_err_z + (Gyr_rawZ/65.5);  //Divide by 65.5 because datasheet says so when using a scale range of 500 degrees per second
      if(i==199)
      {
        Gyr_raw_err_z = Gyr_raw_err_z/200;
        err_Calculated=true;
      }
    }
  } 
  //Circular buffer init 
  values.init(50);
}

void loop() {
  timePrev = time;
  time = millis();
  elapsedTime = (time-timePrev)/1000;

  Wire.beginTransmission(MPU);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 2, true);                 //Request raw data

  Gyr_rawZ = Wire.read()<<8|Wire.read();          //Read Raw value
  Gyr_rawZ = (Gyr_rawZ/65.5) - Gyr_raw_err_z;     //Update raw value
  Gyr_angle_z += Gyr_rawZ*elapsedTime;            //Get the angle difference by multiplying the raw value with the elapsed time
  
  /*We want to use values in the interval [0, 360], so we will do the following*/
  Gyr_angle_z = fmod(Gyr_angle_z, 360);
  while (Gyr_angle_z < 0) Gyr_angle_z +=360; 
  values.put(Gyr_angle_z);                        //Put value in buffer

  /*Looking for a changement in value by calculating the difference between constant signals*/
  if(abs(values.getAverage() - Gyr_angle_z) <= 0.01){   //Check if values are the same
    oldAngle = newAngle;
    newAngle = Gyr_angle_z;
    angleShift = newAngle - oldAngle;
    if (angleShift<-180) angleShift += 360;
    else if (angleShift>180) angleShift -= 360;
    if (abs(angleShift) >= 11.25){
      Serial.println(angleShift);
    }
  }
}
#endif