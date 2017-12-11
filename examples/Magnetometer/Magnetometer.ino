/*
  Example 2 :
  This example reads data from the sensors and calculates :
  - Acceleration in 'g' ( 1 g = 9.8 m/s^2)
  - Rotation speed in dps (degrees per second)
  - Magnetic flux density in μT.
*/

#include <Wire.h>           // include MPU9255 library
#include <Tarsier_MPU9255.h>// include MPU9255 library
float heading, headingDegrees, headingFiltered, declination;

boolean _showProcessingData = true; //toggle show data in processing mode
Tarsier_MPU9255 mpu;

void setup() {
  Wire.begin();           //initialize I2C interface
  Serial.begin(115200);   // initialize Serial port
  mpu.init();             // Initialize MPU9255 chip
}

void loop() {
  // read data from all sensors
  mpu.readMag();
  //save all readings to 'float' variables
  float mx = mpu._MX;
  float my = mpu._MY;
  float mz = mpu._MZ;

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

  //Calculating Heading
  heading = atan2(my, mx);

  // Correcting the heading with the declination angle depending on your location
  // You can find your declination angle at: http://www.ngdc.noaa.gov/geomag-web/
  // At my location it's 8.38 degrees => 0.1462586 rad
  declination = -0.0349066;
  heading += declination;

  // Correcting when signs are reveresed
  if (heading < 0) heading += 2 * PI;
  // Correcting due to the addition of the declination angle
  if (heading > 2 * PI)heading -= 2 * PI;
  headingDegrees = heading * 180 / PI; // The heading in Degrees unit
  // Smoothing the output angle / Low pass filter
  headingFiltered = headingFiltered * 0.85 + headingDegrees * 0.15;

  //Sending the heading value through the Serial Port to Processing IDE
  Serial.println(headingFiltered);


  delay(10);
}
