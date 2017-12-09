/*
  Example 3 :
  This example reads data from the gyroscope and the accelerometer in 4 different scales.
*/

#include <Wire.h>           // include Wire library
#include <Tarsier_MPU9255.h>// include MPU9255 library

Tarsier_MPU9255 mpu;

void print_data()// read and print all data
{
  mpu.readAccel();
  mpu.readGyro();

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
  Serial.println(mpu._GZ);
}


void setup() {
  Wire.begin();           //initialize I2C interface
  Serial.begin(115200);   // initialize Serial port
  mpu.init();             // Initialize MPU9255 chip
}

void loop() {
  /*
    GYRO_FULL_SCALE_250DPS  = 1;
    GYRO_FULL_SCALE_500DPS  = 2;
    GYRO_FULL_SCALE_1000DPS = 3;
    GYRO_FULL_SCALE_2000DPS = 4;
    ACCEL_FULL_SCALE_2G    = 1;
    ACCEL_FULL_SCALE_4G   = 2;
    ACCEL_FULL_SCALE_8G   = 3;
    ACCEL_FULL_SCALE_16G  = 4;
  */
  Serial.println("Gyro scale : +- 250 dps");
  Serial.println("Acc scale  : +- 2g");
  // set gyroscope scale to +- 250 dps and accelerometer scale to +- 2g
  mpu.setScaleAccel(mpu.ACCEL_FULL_SCALE_2G);
  mpu.setScaleGyro(mpu.GYRO_FULL_SCALE_250DPS);
  for (int i = 0; i <= 10; i++) {
    print_data();
    delay(1000);
  }

  Serial.println("Gyro scale : +- 500 dps");
  Serial.println("Acc scale  : +- 4g");
  // set gyroscope scale to +- 500 dps and accelerometer scale to +- 4g
  mpu.setScaleAccel(2);
  mpu.setScaleGyro(2);
  for (int i = 0; i <= 10; i++) //make some readings
  {
    print_data();
    delay(1000);
  }

  Serial.println("Gyro scale : +- 1000 dps");
  Serial.println("Acc scale  : +- 8g");
  // set gyroscope scale to +- 1000 dps and accelerometer scale to +- 8g
  mpu.setScaleAccel(3);
  mpu.setScaleGyro(3);
  for (int i = 0; i <= 10; i++) //make some readings
  {
    print_data();
    delay(1000);
  }

  Serial.println("Gyro scale : +- 2000 dps");
  Serial.println("Acc scale  : +- 16g");
  // set gyroscope scale to +- 2000 dps and accelerometer scale to +- 16g
  mpu.setScaleAccel(4);
  mpu.setScaleGyro(4);
  for (int i = 0; i <= 10; i++) //make some readings
  {
    print_data();
    delay(1000);
  }
}
