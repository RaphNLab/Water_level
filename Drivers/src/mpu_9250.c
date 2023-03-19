/*
 * mpu_9250.c
 *
 *  Created on: Mar 11, 2023
 *      Author: silvere
 */

#include "mpu_9250.h"



HAL_StatusTypeDef MPU_9250WhoAmI(uint8_t *reg)
{
	/*HAL_StatusTypeDef retVal = HAL_ERROR;
	reg[0] = (uint8_t)WHO_AM_I;

	retVal =  HAL_I2C_Master_Transmit(&hi2c1, MPU9250_ADDR, reg, 1, HAL_MAX_DELAY);
	if(retVal == HAL_ERROR)
	{
		//Report error while writing
	}
	else
	{
		retVal = HAL_I2C_Master_Receive(&hi2c1, MPU9250_ADDR, reg[0], 1, HAL_MAX_DELAY);
		if(retVal == HAL_ERROR)
		{
			//Report error while reading
		}
	}
	return retVal;*/
}


void MPU_9250Init(void)
{

}

void MPU_9250GetTemp(float *temp)
{

}


void MPU_9250GetAccAxis(uint8_t *xAxis, uint8_t *yAxis, uint8_t *zAxis)
{

}

void MPU_9250GetGyroAxis(uint8_t *xAxis, uint8_t *yAxis, uint8_t *zAxis)
{

}



