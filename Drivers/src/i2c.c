/*
 * i2c.c
 *
 *  Created on: Mar 11, 2023
 *      Author: silvere
 */



#include "i2c.h"

uint8_t i2cRxBuffer[10];
uint8_t i2cTxBuffer[10];
I2C_HandleTypeDef hi2c1;
I2cDev_T i2cDev;



/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
void i2cSetup(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
	  while(1);
  }
}

void i2cgpioSetup(void)
{
	GPIO_InitTypeDef gpio_i2c;
	/* Reset all struct members */
	memset(&gpio_i2c, 0, sizeof(gpio_i2c));

	/**I2C1 GPIO Configuration
	PB8     ------> I2C1_SCL
	PB9     ------> I2C1_SDA
	*/
	gpio_i2c.Pin = GPIO_PIN_8|GPIO_PIN_9;
	gpio_i2c.Mode = GPIO_MODE_AF_OD;
	gpio_i2c.Pull = GPIO_NOPULL;
	gpio_i2c.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_i2c.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &gpio_i2c);
}


/**
* @brief I2C MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void i2cHardwareSetup(void)
{
	/* Peripheral clock enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();

	i2cSetup();
	i2cgpioSetup();
}

void i2cDevConfig(I2cDev_T *i2cDev, I2C_HandleTypeDef *hi2c, uint8_t *rxBuffer, uint8_t *txBuffer, uint8_t size)
{
	if(i2cDev == NULL)
	{
		// Report invalid device pointer
	}
	else if (txBuffer == NULL)
	{
		// Report invalid buffer pointer
	}
	else if (rxBuffer == NULL)
	{
		// Report invalid buffer pointer
	}
	else
	{
		i2cDev->hi2c = hi2c;
		i2cDev->i2cRxBuffer = rxBuffer;
		i2cDev->i2cTxBuffer = txBuffer;
		i2cDev->size = size;

		i2cHardwareSetup();
	}
}


void i2c_Xfer(I2cDev_T *i2cDev, uint8_t *rxbuffer, uint8_t size)
{
	//HAL_SPI_Transmit(&hspi1, &temp_data, 1, 100);
	//HAL_SPI_Receive(&hspi1, data, len, 100);
	//HAL_I2C_Master_Transmit();
	//i2cDev->hi2c->Instance->SR1 &
}


/**
  * @brief This function handles I2C global interrupt.
  */
void I2C1_IRQHandler(void)
{


}



