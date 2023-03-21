/*
 * mpu_9250.c
 *
 *  Created on: Mar 11, 2023
 *      Author: silvere
 */

#include "mpu_9250.h"
//#include "spi.h"
#include "i2c.h"



uint8_t MPU_9250WhoAmI(void)
{
	uint8_t reg[2] = {0};
	HAL_StatusTypeDef retVal = HAL_ERROR;
	reg[0] = (uint8_t)WHO_AM_I;

	retVal =  HAL_I2C_Master_Transmit(&hi2c1, MPU9250_ADDR, reg, 1, HAL_MAX_DELAY);
	if(retVal == HAL_ERROR)
	{
		//Report error while writing
	}
	else
	{
		retVal = HAL_I2C_Master_Receive(&hi2c1, MPU9250_ADDR, (reg+1), 1, HAL_MAX_DELAY);
		if(retVal == HAL_ERROR)
		{
			//Report error while reading
		}
	}
	return reg[1];
}


void MPU_9250Init(void)
{

}

void MPU_9250GetTemp(float *temp)
{
	uint16_t rawTemperature = 0;
	uint8_t tempHByte = 0;
	uint8_t tempLByte = 0;
	uint8_t reg[2] = {0};
	HAL_StatusTypeDef retVal = HAL_ERROR;
	reg[0] = (uint8_t)TEMP_OUT_H;

	retVal =  HAL_I2C_Master_Transmit(&hi2c1, MPU9250_ADDR, reg, 1, HAL_MAX_DELAY);
	if(retVal == HAL_ERROR)
	{
		//Report error while writing
	}
	else
	{
		retVal = HAL_I2C_Master_Receive(&hi2c1, MPU9250_ADDR, (reg+1), 1, HAL_MAX_DELAY);
		if(retVal == HAL_ERROR)
		{
			//Report error while reading
		}
		tempHByte = reg[1];
	}


	reg[0] = (uint8_t)TEMP_OUT_L;

	retVal =  HAL_I2C_Master_Transmit(&hi2c1, MPU9250_ADDR, reg, 1, HAL_MAX_DELAY);
	if(retVal == HAL_ERROR)
	{
		//Report error while writing
	}
	else
	{
		retVal = HAL_I2C_Master_Receive(&hi2c1, MPU9250_ADDR, (reg+1), 1, HAL_MAX_DELAY);
		if(retVal == HAL_ERROR)
		{
			//Report error while reading
		}
		tempLByte = reg[1];
	}
	rawTemperature = ((uint16_t) (tempHByte << 8)) | ((uint16_t) tempLByte);

	*temp = ((float) rawTemperature) / 333.87f + 21.0f;
}


void MPU_9250GetAccAxis(uint8_t *xAxis, uint8_t *yAxis, uint8_t *zAxis)
{

}

void MPU_9250GetGyroAxis(uint8_t *xAxis, uint8_t *yAxis, uint8_t *zAxis)
{

}



