#include <Arduino.h>
#include <Wire.h>

float elapsedTime, time, timePrev;        //Variables for time control
int gyro_error=0;                         //We use this variable to only calculate once the gyro data error
int16_t Gyr_rawX, Gyr_rawY, Gyr_rawZ;     //Here we store the raw data read 
float Gyro_angle_x, Gyro_angle_y, Gyro_angle_z;             //Here we store the angle value obtained with Gyro data
float Gyro_raw_error_x, Gyro_raw_error_y, Gyro_raw_error_z; //Here we store the initial gyro data error

void setup() {
  // put your setup code here, to run once:
  Wire.begin();                           //begin the wire comunication  
  Wire.beginTransmission(0x68);           //begin, Send the slave adress (in this case 68)  
  Wire.write(0x6B);                       //make the reset (place a 0 into the 6B register)
  Wire.write(0x07);
  Wire.endTransmission(true);             //end the transmission
  
  Wire.beginTransmission(0x68);           //begin, Send the slave adress (in this case 68) 
  Wire.write(0x1B);                       //We want to write to the GYRO_CONFIG register (1B hex)
  Wire.write(0x10);                       //Set the register bits as 00010000 (1000dps full scale)
  Wire.endTransmission(true);             //End the transmission with the gyro

  Serial.begin(9600);                     //Remember to set this same baud rate to the serial monitor  
  time = millis();                        //Start counting time in milliseconds
/*Here we calculate the gyro data error before we start the loop
 * I make the mean of 200 values, that should be enough*/
  if(gyro_error==0)
  {
    for(int i=0; i<200; i++)
    {
      Wire.beginTransmission(0x68);            //begin, Send the slave adress (in this case 68) 
      Wire.write(0x43);                        //First adress of the Gyro data
      Wire.endTransmission(false);
      Wire.requestFrom(0x68,6,true);           //We ask for just 6 registers 
         
      Gyr_rawX=Wire.read()<<8|Wire.read();     //Once again we shif and sum
      Gyr_rawY=Wire.read()<<8|Wire.read();
      Gyr_rawZ=Wire.read()<<8|Wire.read();
   
      /*---X---*/
      Gyro_raw_error_x = Gyro_raw_error_x + (Gyr_rawX/32.8); 
      /*---Y---*/
      Gyro_raw_error_y = Gyro_raw_error_y + (Gyr_rawY/32.8);
      /*---Z---*/
      Gyro_raw_error_z = Gyro_raw_error_z + (Gyr_rawZ/32.8);
      if(i==199)
      {
        Gyro_raw_error_x = Gyro_raw_error_x/200;
        Gyro_raw_error_y = Gyro_raw_error_y/200;
        Gyro_raw_error_z = Gyro_raw_error_z/200;
        gyro_error=1;
      }
    }
  }  
}//end of setup void






void loop() {
    timePrev = time;                        // the previous time is stored before the actual time read
    time = millis();                        // actual time read
    elapsedTime = (time - timePrev) / 1000; //divide by 1000 in order to obtain seconds

    
//////////////////////////////////////Gyro read/////////////////////////////////////

    Wire.beginTransmission(0x68);            //begin, Send the slave adress (in this case 68) 
    Wire.write(0x43);                        //First adress of the Gyro data
    Wire.endTransmission(false);
    Wire.requestFrom(0x68,6,true);           //We ask for 6 registers
        
    Gyr_rawX=Wire.read()<<8|Wire.read();     //Once again we shif and sum
    Gyr_rawY=Wire.read()<<8|Wire.read();
    Gyr_rawZ=Wire.read()<<8|Wire.read();
    /*Now in order to obtain the gyro data in degrees/seconds we have to divide first
    the raw value by 32.8 because that's the value that the datasheet gives us for a 1000dps range*/
    /*---X---*/
    Gyr_rawX = (Gyr_rawX/32.8) - Gyro_raw_error_x; 
    /*---Y---*/
    Gyr_rawY = (Gyr_rawY/32.8) - Gyro_raw_error_y;
    /*---Z---*/
    Gyr_rawZ = (Gyr_rawZ/32.8) - Gyro_raw_error_z;

    /*Now we integrate the raw value in degrees per seconds in order to obtain the angle
    * If you multiply degrees/seconds by seconds you obtain degrees */
    /*---X---*/
    Gyro_angle_x = Gyro_angle_x  + Gyr_rawX*elapsedTime;
    /*---Y---*/
    Gyro_angle_y = Gyro_angle_y  + Gyr_rawY*elapsedTime;
    /*---Z---*/
    Gyro_angle_z = Gyro_angle_z  + Gyr_rawZ*elapsedTime;

    Serial.println(Gyro_angle_z);
}