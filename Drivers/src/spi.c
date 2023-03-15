/*
 * spi.c
 *
 *  Created on: Mar 11, 2023
 *      Author: silvere
 */


#include "spi.h"

uint8_t spiRxBuffer[10];
uint8_t spiTxBuffer[10];
SPI_HandleTypeDef hspi1;
SpiDev_T spiDev;


/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
void spiSetup(void)
{

  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_SLAVE;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_INPUT;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
	  while(1);
  }
}

/**
* @brief SPI MSP Initialization
* This function configures the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void spiGpioSetup(void)
{
	GPIO_InitTypeDef gpio_spi;

	/* Reset all struct members */
	memset(&gpio_spi, 0, sizeof(gpio_spi));

	gpio_spi.Pin = SPI_SLK|SPI_MISO|SPI_MOSI;
	gpio_spi.Mode = GPIO_MODE_AF_PP;
	gpio_spi.Pull = GPIO_NOPULL;
	gpio_spi.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_spi.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOB, &gpio_spi);

	/* SPI1 interrupt Init */
	HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(SPI1_IRQn);
}

void spiHardwareSetup(void)
{
	__HAL_RCC_SPI1_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	spiSetup();
	spiGpioSetup();
}

void spiDevConfig(SpiDev_T *spiDev, SPI_HandleTypeDef *hspi, uint8_t *rxBuffer, uint8_t *txBuffer, uint8_t size)
{
	if(spiDev == NULL)
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
		spiDev->spi = hspi;
		spiDev->spiRxBuffer = rxBuffer;
		spiDev->spiTxBuffer = txBuffer;
		spiDev->size = size;

		spiHardwareSetup();
	}
}


void spiSendCmd(SpiDev_T *spiDev, uint8_t *rxBuffer, uint8_t size)
{

}

void spiGetData(SpiDev_T *spiDev, uint8_t *txBuffer, uint8_t size)
{

}


/**
  * @brief This function handles SPI1 global interrupt.
  */
void SPI1_IRQHandler(void)
{


}

