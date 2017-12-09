/*
* Tarsier_MPU9255.cpp
*
* Created: 12/9/2017 7:07:32 PM
* Author: TARSIER
*/


#include "Tarsier_MPU9255.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
// default constructor
Tarsier_MPU9255::Tarsier_MPU9255()
{
} //Tarsier_MPU9255

void Tarsier_MPU9255::mpuReadBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest){
	Wire.beginTransmission(address);
	Wire.write(subAddress);
	Wire.endTransmission(false);
	uint8_t i = 0;
	Wire.requestFrom(address, count);
	while (Wire.available()) {
		dest[i++] = Wire.read();
	}
}

uint8_t Tarsier_MPU9255::mpuReadByte(uint8_t address, uint8_t subAddress){
	uint8_t data;
	Wire.beginTransmission(address);
	Wire.write(subAddress);
	Wire.endTransmission(false);
	Wire.requestFrom(address, (uint8_t) 1);
	data = Wire.read();
	return data;
}

void Tarsier_MPU9255::mpuWriteByte(uint8_t address, uint8_t subAddress, uint8_t data){
	Wire.beginTransmission(address);
	Wire.write(subAddress);
	Wire.write(data);
	Wire.endTransmission();
}

void Tarsier_MPU9255::init(){
	Wire.begin();
	// MPU9255 init procedure
	mpuWriteByte(MPU_ADDRESS,PWR_MGMT_2, 0b00000000); // enable gyro and acc
	mpuWriteByte(MPU_ADDRESS,CONFIG, 0x03); // set DLPF_CFG to 11
	mpuWriteByte(MPU_ADDRESS,SMPLRT_DIV, 0x04);// set prescaler sample rate to 4
	uint8_t c = mpuReadByte(MPU_ADDRESS,GYRO_CONFIG);
	mpuWriteByte(MPU_ADDRESS,GYRO_CONFIG, c & ~0x02);// set second option from tavle
	mpuWriteByte(MPU_ADDRESS,GYRO_CONFIG, c & ~0x18);// set scale to +- 250 dps
	c = mpuReadByte(MPU_ADDRESS,ACCEL_CONFIG);
	mpuWriteByte(MPU_ADDRESS,ACCEL_CONFIG, c & ~0x18); // set scale to +- 2G
	
	mpuWriteByte(MPU_ADDRESS,INT_PIN_CFG, 0x22);// BYPASS ENABLE, LATCH_INT_EN
	mpuWriteByte(MPU_ADDRESS,INT_ENABLE, 0x01); // RAW_RDY_EN

	// magnetometer init procedure
	mpuWriteByte(MAG_ADDRESS, CNTL, 0x00);
	delay(10);
	mpuWriteByte(MAG_ADDRESS, CNTL, 0x16);
	delay(10);
	
	// set default full scale range for gyro and accel
	setScaleGyro(GYRO_FULL_SCALE_250DPS);
	setScaleAccel(ACCEL_FULL_SCALE_8G);
}


void Tarsier_MPU9255::setScaleAccel(uint8_t value){
	uint8_t val= mpuReadByte(MPU_ADDRESS,ACCEL_CONFIG);
	switch(value){
		case 1:// +- 2g
		val &= ~((1<<3)|(1<<4));// set bit 3 and 4 to 0
		break;
		case 2:// +- 4g
		val &= ~(1<<4);// set bit 4 to zero
		val |= (1<<3);// set bit 3 to 1
		break;
		case 3:// +- 8g
		val &= ~(1<<3);// set bit 3 to zero
		val |= (1<<4);// set bit 4 to 1
		break;
		case 4:// +- 16g
		val |= (1<<4)|(1<<3);// set bit 3 and 4 to 1
		break;
	}
	mpuWriteByte(MPU_ADDRESS,ACCEL_CONFIG,val);// commit changes
}

void Tarsier_MPU9255::setScaleGyro(uint8_t value){
	uint8_t val= mpuReadByte(MPU_ADDRESS,GYRO_CONFIG);
	switch(value)	{
		case 1:// +- 250 dps
		val &= ~((1<<3)|(1<<4));// set bit 3 and 4 to 0
		break;
		case 2:// +- 500 dps
		val &= ~(1<<4);// set bit 4 to zero
		val |= (1<<3);// set bit 3 to 1
		break;
		case 3:// +- 1000 dps
		val &= ~(1<<3);// set bit 3 to zero
		val |= (1<<4);// set bit 4 to 1
		break;
		case 4:// +- 2000 dps
		val |= (1<<4)|(1<<3);// set bit 3 and 4 to 1
		break;
	}
	mpuWriteByte(MPU_ADDRESS,GYRO_CONFIG,val);// commit changes
}


void Tarsier_MPU9255::readAccel(){
	uint8_t rawData[6];
	mpuReadBytes(MPU_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);
	//data processing
	_AX = ((int16_t)rawData[0] << 8) | rawData[1] ;
	_AY = ((int16_t)rawData[2] << 8) | rawData[3] ;
	_AZ = ((int16_t)rawData[4] << 8) | rawData[5] ;
}

void Tarsier_MPU9255::readAccel(int16_t * destination){
	uint8_t rawData[6];
	mpuReadBytes(MPU_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);
	destination[0] = (((int16_t)rawData[0] << 8) | rawData[1]);
	destination[1] = (((int16_t)rawData[2] << 8) | rawData[3]);
	destination[2] = (((int16_t)rawData[4] << 8) | rawData[5]);
}

void Tarsier_MPU9255::readGyro(){
	uint8_t rawData[6];
	mpuReadBytes(MPU_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);
	_GX = ((int16_t)rawData[0] << 8) | rawData[1] ;
	_GY = ((int16_t)rawData[2] << 8) | rawData[3] ;
	_GZ = ((int16_t)rawData[4] << 8) | rawData[5] ;
}

void Tarsier_MPU9255::readGyro(int16_t * destination){
	uint8_t rawData[6];
	mpuReadBytes(MPU_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);
	destination[0] = (((int16_t)rawData[0] << 8) | rawData[1]);
	destination[1] = (((int16_t)rawData[2] << 8) | rawData[3]);
	destination[2] = (((int16_t)rawData[4] << 8) | rawData[5]);
}

void Tarsier_MPU9255::readMag(){
	uint8_t rawData[7];
	if (mpuReadByte(MAG_ADDRESS, ST1) & 0x01) {
		mpuReadBytes(MAG_ADDRESS, MAG_XOUT_L, 7, &rawData[0]);
		uint8_t c = rawData[6];
		if (!(c & 0x08)) {
			// process data
			_MX=((int16_t)rawData[1] << 8) | rawData[0] ;
			_MY=((int16_t)rawData[3] << 8) | rawData[2] ;
			_MZ=((int16_t)rawData[5] << 8) | rawData[4] ;
		}
	}
	mpuReadByte(MAG_ADDRESS,0x09); //This tells the Mag Module to take another measurement.
}

void  Tarsier_MPU9255::readMag(int16_t * destination){
	uint8_t rawData[7];
	if (mpuReadByte(MAG_ADDRESS, ST1) & 0x01) {
		mpuReadBytes(MAG_ADDRESS, MAG_XOUT_L, 7, &rawData[0]);
		uint8_t c = rawData[6];
		if (!(c & 0x08)) {
			destination[0] = ((int16_t)rawData[1] << 8) | rawData[0];
			destination[1] = ((int16_t)rawData[3] << 8) | rawData[2];
			destination[2] = ((int16_t)rawData[5] << 8) | rawData[4];
		}
	}
	mpuReadByte(MAG_ADDRESS,0x09); //This tells the Mag Module to take another measurement.
}

// default destructor
Tarsier_MPU9255::~Tarsier_MPU9255()
{
} //~Tarsier_MPU9255
