/*
  Example 1 :
  This example initializes the sensors and outputs raw data from Gyroscope, Accelerometer and Magnetometer.

*/

#include <Wire.h>// include Wire library
#include <Tarsier_MPU9255.h>// include MPU9255 library

Tarsier_MPU9255 mpu;

void setup() {
  Wire.begin();         //initialize I2C interface
  Serial.begin(115200); // initialize Serial port
  mpu.init();           // Initialize MPU9255 chip
}

void loop() {
  mpu.readAccel();  // read data from accelerometer
  mpu.readGyro();   // get data from gyroscope
  mpu.readMag();    // get data from the magnetometer

  // print all data in serial monitor
  Serial.print("AX: ");
  Serial.print(mpu._AX); Serial.print("\t");
  Serial.print("AY: ");
  Serial.print(mpu._AY); Serial.print("\t");
  Serial.print("AZ: ");
  Serial.print(mpu._AZ); Serial.print("\t");
  Serial.print("GX: ");
  Serial.print(mpu._GX); Serial.print("\t");
  Serial.print("GY: ");
  Serial.print(mpu._GY); Serial.print("\t");
  Serial.print("GZ: ");
  Serial.print(mpu._GZ); Serial.print("\t");
  Serial.print("MX: ");
  Serial.print(mpu._MX);  Serial.print("\t");
  Serial.print("MY: ");
  Serial.print(mpu._MY);  Serial.print("\t");
  Serial.print(" MZ: ");
  Serial.println(mpu._MZ);

  delay(100);
}
