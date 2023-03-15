/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "global.h"
#include "uart.h"
#include "i2c.h"
#include "spi.h"
#include "mpu_9250.h"

TaskHandle_t xTaskHandle1 = NULL;
TaskHandle_t xTaskHandle2 = NULL;


/* functions prototypes */
void vApplicationTickHook(void);

void vTaskHandler(void *params);
void vLedTaskHandler(void *params);
void vUartCmadTaskHandler(void *params);
void vUartHandleCmd(UartDev_T *uartDev);
void SystemClock_Config(void);
void Error_Handler(void);


int main(void)
{

	/*Reset RCC clock configuration to the default reset state*/
	HAL_RCC_DeInit();


	/* Update the SystemCoreClock variable*/
	SystemCoreClockUpdate();

	uartDevConfig(&uartDev, &huart2, uartRxBuffer, uartTxBuffer, 0);
	i2cDevConfig(&i2cDev, &hi2c1, i2cRxBuffer, i2cTxBuffer, 0);
	spiDevConfig(&spiDev, &hspi1, spiRxBuffer, spiTxBuffer, 0);

	/* Create 2 task with the same priority */
	//xTaskCreate(vTaskHandler, "Task 1", configMINIMAL_STACK_SIZE, (void *)"Hello From task 1\r\n", 1, &xTaskHandle1);

	//xTaskCreate(vTaskHandler, "Send string", configMINIMAL_STACK_SIZE, (void *)"Hello From task 2\r\n", 2, &xTaskHandle2);

	xTaskCreate(vUartCmadTaskHandler, "Command handler", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	//xTaskCreate(vLedTaskHandler, "LED Task", configMINIMAL_STACK_SIZE, (void *)"1000", 1, NULL);
	//xTaskCreate(vLedTaskHandler, "LED Task", configMINIMAL_STACK_SIZE, (void *)"500", 1, NULL);

	/* Start the scheduler: This function will never return */
	vTaskStartScheduler();

	for(;;);
}


void vUartCmadTaskHandler(void *params)
{
	while(1)
	{
		vUartHandleCmd(&uartDev);
		vUartHandleCmd(&uartDev);
	}
}

void vUartHandleCmd(UartDev_T *uartDev)
{
	if(uartDev->uartRxFlag == UART_RX_CMP)
	{
		if((strncmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_GET_TEMP], uartDev->size)) == 0)
		{
			// Call Temperature task
			// Blink LED 1/2 second
		}
		else if((strncmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_GET_ACC], uartDev->size)) == 0)
		{
			// Call accelerometer
			// Print angle every 2 seconds
			// Turn LED every 1 second
		}
		else if((strncmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_3_OFF], uartDev->size)) == 0)
		{
			// Torn on LED
			HAL_GPIO_WritePin(GPIOA, LED3_PIN, GPIO_PIN_SET);
		}
		else if((strncmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_3_ON], uartDev->size)) == 0)
		{
			// Turn off led
			HAL_GPIO_WritePin(GPIOA, LED3_PIN, GPIO_PIN_RESET);
		}
		else if((strncmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_4_OFF], uartDev->size)) == 0)
		{
			// Torn on LED
			HAL_GPIO_WritePin(GPIOA, LED4_PIN, GPIO_PIN_SET);
		}
		else if((strncmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_4_ON], uartDev->size)) == 0)
		{
			// Turn off led
			HAL_GPIO_WritePin(GPIOA, LED4_PIN, GPIO_PIN_RESET);
		}
		else if((strncmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_5_OFF], uartDev->size)) == 0)
		{
			// Torn on LED
			HAL_GPIO_WritePin(GPIOA, LED5_PIN, GPIO_PIN_SET);
		}
		else if((strncmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_5_ON], uartDev->size)) == 0)
		{
			// Turn off led
			HAL_GPIO_WritePin(GPIOA, LED5_PIN, GPIO_PIN_RESET);
		}
		else if((strncmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_6_OFF], uartDev->size)) == 0)
		{
			// Torn on LED
			HAL_GPIO_WritePin(GPIOA, LED6_PIN, GPIO_PIN_SET);
		}
		else if((strncmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_6_ON], uartDev->size)) == 0)
		{
			// Turn off led
			HAL_GPIO_WritePin(GPIOA, LED6_PIN, GPIO_PIN_RESET);
		}
		else
		{
			// Report invalid command
			uartSendStr(uartDev, (uint8_t *)"Invalid CMD\r\n", strlen((const char*)"Invalid CMD\r\n"));
		}
		// Reset the flag
		uartDev->uartRxFlag = UART_NO_RX;
		memErase(uartDev->uartRxBuffer, uartDev->size);
	}
}


void vLedTaskHandler(void *params){

	uint16_t delay;
	char *param;
	param = (char *)params;
	delay = atoi(param);

	const TickType_t xDelay250ms = pdMS_TO_TICKS(delay);

	while(1)
	{
		HAL_GPIO_TogglePin(GPIOA, LED5_PIN);
		vTaskDelay(xDelay250ms);
	}
}


void vTaskHandler(void *params)
{
	const TickType_t xDelay250ms = pdMS_TO_TICKS(250);

	unsigned char *pcTaskName;
	pcTaskName = (unsigned char *)params;
	while(1)
	{
		//uartPuts(pcTaskName);
		//uartSendStr(&uartDev, pcTaskName, strlen((const char*)pcTaskName));

		vTaskDelay(xDelay250ms);
	}
}

void vApplicationTickHook(void)
{

}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
