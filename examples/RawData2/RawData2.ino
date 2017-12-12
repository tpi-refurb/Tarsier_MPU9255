/*
  Example 2 :
  This example initializes the sensors and outputs raw data from Gyroscope, Accelerometer and Magnetometer.
  The same with example #1 (RawData.ino) but in different approach

*/

#include <Wire.h>// include Wire library
#include <Tarsier_MPU9255.h>// include MPU9255 library

Tarsier_MPU9255 mpu;
int16_t _gyro[3], _accel[3], _mag[3];

void setup() {
  Wire.begin();         //initialize I2C interface
  Serial.begin(115200); // initialize Serial port
  mpu.init();           // Initialize MPU9255 chip
}

void loop() {
  mpu.readAccel(_accel);  // read data from accelerometer
  mpu.readGyro(_gyro);   // get data from gyroscope
  mpu.readMag(_mag);    // get data from the magnetometer

  // print all data in serial monitor
  Serial.print("AX: ");
  Serial.print(_accel[0]); Serial.print("\t");
  Serial.print("AY: ");
  Serial.print(_accel[1]); Serial.print("\t");
  Serial.print("AZ: ");
  Serial.print(_accel[2]); Serial.print("\t");

  Serial.print("GX: ");
  Serial.print(_gyro[0]); Serial.print("\t");
  Serial.print("GY: ");
  Serial.print(_gyro[1]); Serial.print("\t");
  Serial.print("GZ: ");
  Serial.print(_gyro[2]); Serial.print("\t");

  Serial.print("MX: ");
  Serial.print(_mag[0]);  Serial.print("\t");
  Serial.print("MY: ");
  Serial.print(_mag[1]);  Serial.print("\t");
  Serial.print(" MZ: ");
  Serial.println(_mag[2]);

  delay(10);
}
