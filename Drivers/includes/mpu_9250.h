/*
 * mpu_9250.h
 *
 *  Created on: Mar 11, 2023
 *      Author: silvere
 */

#ifndef INCLUDES_MPU_9250_H_
#define INCLUDES_MPU_9250_H_

#include "global.h"


#define PWR_MGMT_1 		0x6B
#define XG_OFFSET_H		0x13
#define XG_OFFSET_L		0x14
#define YG_OFFSET_H		0x15
#define YG_OFFSET_L		0x16
#define ZG_OFFSET_H		0x17
#define ZG_OFFSET_L		0x18

#define GYRO_CONFIG		0x1B
#define ACCEL_CONFIG	0x1C
#define ACCEL_CONFIG_2	0x1D
#define LP_ACCEL_ODR	0x1E

#define ACCEL_XOUT_H	0x3B
#define ACCEL_XOUT_L	0x3C
#define ACCEL_YOUT_H	0x3D
#define ACCEL_YOUT_L	0x3E
#define ACCEL_ZOUT_H	0x3F
#define ACCEL_ZOUT_L	0x40
#define TEMP_OUT_H		0x41
#define TEMP_OUT_L		0x42
#define GYRO_XOUT_H		0x43
#define GYRO_XOUT_L		0x44
#define GYRO_YOUT_H		0x45
#define GYRO_YOUT_L		0x46
#define GYRO_ZOUT_H		0x47
#define GYRO_ZOUT_L		0x48

#define WHO_AM_I		0x75

#define MPU9250_ADDR 	(0x68 << 1)


uint8_t MPU_9250WhoAmI(void);
void MPU_9250Init(void);
void MPU_9250GetTemp(float *temp);

void MPU_9250GetAccAxis(uint8_t *xAxis, uint8_t *yAxis, uint8_t *zAxis);
void MPU_9250GetGyroAxis(uint8_t *xAxis, uint8_t *yAxis, uint8_t *zAxis);


#endif /* INCLUDES_MPU_9250_H_ */
