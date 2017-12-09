/* 
* Tarsier_MPU9255.h
*
* Created: 12/9/2017 7:07:32 PM
* Author: TARSIER
*/


#ifndef __Tarsier_MPU9255_H__
#define __Tarsier_MPU9255_H__

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Wire.h>

//############################################# Definitions #############################################

// definitions of sensors adresses
#define MPU_ADDRESS			0x68	// main chip adress
#define MAG_ADDRESS			0x0C	// magnetometer

// registers adresses

//control registers
#define USER_CTRL			0x6A
#define PWR_MGMT_2			0x6B
#define INT_PIN_CFG			0x37
#define ST1					0x02
//#define ST2 0x09
#define CNTL				0x0A
#define ACCEL_CONFIG		0x1C
#define ACCEL_CONFIG2		0x1D
#define GYRO_CONFIG			0x1B
#define CONFIG				0x1A
#define SMPLRT_DIV			0x19
#define GYRO_CONFIG			0x1B
#define ACCEL_CONFIG		0x1C
#define INT_PIN_CFG			0x37
#define INT_ENABLE			0x38

// data registers

// magnetometer
#define MAG_XOUT_L			0x03

// gyroscope
#define GYRO_XOUT_H			0x43

//accelerometer
#define ACCEL_XOUT_H		0x3B

class Tarsier_MPU9255
{
//variables
public:
	int16_t _AX,_AY,_AZ=0;	// handles for accel values
	int16_t _GX,_GY,_GZ=0; // handles for gyro values
	int16_t _MX,_MY,_MZ=0; // handles for mag values
	
	uint8_t GYRO_FULL_SCALE_250DPS	= 1;
	uint8_t GYRO_FULL_SCALE_500DPS  = 2;
	uint8_t GYRO_FULL_SCALE_1000DPS = 3;
	uint8_t GYRO_FULL_SCALE_2000DPS = 4;
	
	uint8_t ACCEL_FULL_SCALE_2G		= 1;
	uint8_t ACCEL_FULL_SCALE_4G		= 2;
	uint8_t ACCEL_FULL_SCALE_8G		= 3;
	uint8_t ACCEL_FULL_SCALE_16G	= 4;


protected:
private:

//functions
public:
	Tarsier_MPU9255();
	~Tarsier_MPU9255();
	void init();
	void setScaleAccel(uint8_t value);
	void setScaleGyro(uint8_t value);	
	// ---- Data read functions -----
	void readAccel();
	void readAccel(int16_t * destination);
	void readGyro();
	void readGyro(int16_t * destination);
	void readMag();
	void readMag(int16_t * destination);
	
protected:
private:
	Tarsier_MPU9255( const Tarsier_MPU9255 &c );
	Tarsier_MPU9255& operator=( const Tarsier_MPU9255 &c );
	uint8_t mpuReadByte(uint8_t address, uint8_t subAddress);
	void mpuReadBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest);
	void mpuWriteByte(uint8_t address, uint8_t subAddress, uint8_t data);


}; //Tarsier_MPU9255

#endif //__Tarsier_MPU9255_H__
