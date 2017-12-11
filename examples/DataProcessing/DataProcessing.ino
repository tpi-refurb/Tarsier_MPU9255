/*
  Example 2 :
  This example reads data from the sensors and calculates :
  - Acceleration in 'g' ( 1 g = 9.8 m/s^2)
  - Rotation speed in dps (degrees per second)
  - Magnetic flux density in μT.
*/

#include <Wire.h>           // include MPU9255 library
#include <Tarsier_MPU9255.h>// include MPU9255 library

Tarsier_MPU9255 mpu;

void setup() {
  Wire.begin();           //initialize I2C interface
  Serial.begin(115200);   // initialize Serial port
  mpu.init();             // Initialize MPU9255 chip
}

void loop() {
  // read data from all sensors
  mpu.readAccel();
  mpu.readGyro();
  mpu.readMag();
  //save all readings to 'float' variables
  float ax = mpu._AX;
  float ay = mpu._AY;
  float az = mpu._AZ;

  float gx = mpu._GX;
  float gy = mpu._GY;
  float gz = mpu._GZ;

  float mx = mpu._MX;
  float my = mpu._MY;
  float mz = mpu._MZ;


  // do the math :

  /*---- Acceleration ----*/
  /*
    To get acceleration in 'g', each reading has to be divided by :
    -> 16384 for +- 2g scale (default value)
    -> 8192  for +- 4g scale
    -> 4096  for +- 8g scale
    -> 2048  for +- 16g scale
  */
  ax = ax / 16384;
  ay = ay / 16384;
  az = az / 16384;

  /*---- Gyroscope data ----*/
  /*
    To get rotation in dps (degrees per second), each reading has to be divided by :
    -> 131   for +- 250  dps scale (default value)
    -> 65.5  for +- 500  dps scale
    -> 32.8  for +- 1000 dps scale
    -> 16.4  for +- 2000 dps scale

  */
  gx = gx / 131;
  gy = gy / 131;
  gz = gz / 131;

  /*---- Magnetic flux ----*/
  /*
    To get magnetic flux density in μT, each reading has to be multiplied by some number (calibration) and then divided by 0.6.
    (Faced North each axis should output arround 31 µT) (without any metal / walls around)
    Note : This manetometer has really low initial calibration tolerance : +- 500 unit ( 833,3 μT ) !!!
    Scale of the magnetometer is fixed -> +- 4800 μT.
  */
  const float cal = 0.06;
  mx = mx * cal;
  my = my * cal;
  mz = mz * cal;
  mx = mx / 0.6;
  my = my / 0.6;
  mz = mz / 0.6;

  // print all data
  Serial.print("AX: ");
  Serial.print(ax);
  Serial.print(" g"); Serial.print("\t");
  Serial.print("AY: ");
  Serial.print(ay);
  Serial.print(" g"); Serial.print("\t");
  Serial.print(" AZ: ");
  Serial.print(az);
  Serial.print(" g"); Serial.print("\t");
  Serial.print("GX: ");
  Serial.print(gx);
  Serial.print(" dps"); Serial.print("\t");
  Serial.print("GY: ");
  Serial.print(gy);
  Serial.print(" dps"); Serial.print("\t");
  Serial.print("GZ: ");
  Serial.print(gz);
  Serial.print(" dps"); Serial.print("\t");
  Serial.print("MX: ");
  Serial.print(mx);
  Serial.print(" qT"); Serial.print("\t");
  Serial.print(" MY: ");
  Serial.print(my);
  Serial.print(" qT"); Serial.print("\t");
  Serial.print("MZ: ");
  Serial.print(mz);
  Serial.println(" qT");
  delay(100);
}
