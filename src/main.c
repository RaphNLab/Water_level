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



typedef enum
{
	ACCELEROMETER_TASK = 0,
	GYROSCOPE_TASK,
	TEMPERATURE_TASK,
	DEFAULT_TASK
}TaskType_T;


uint16_t ledDelay = 0;
uint8_t notify = 0;

TaskHandle_t xledTaskHandle = NULL;
TaskHandle_t xaccTaskHandle = NULL;
TaskHandle_t xtempTaskHandle = NULL;
TaskHandle_t xtimerTaskHandle = NULL;
TaskHandle_t xuartTaskHandle = NULL;

TaskType_T taskType = DEFAULT_TASK;

/* functions prototypes */


void vLedTaskHandler(void *params);
void vAccTaskHandler(void *params);
void vTempTaskHandler(void *params);
void vUartCmdTaskHandler(void *params);
void vUartHandleCmd(UartDev_T *uartDev);

void SystemClock_Config(void);
void Error_Handler(void);
void rtosDelay(uint16_t delay);

int main(void)
{

	/*Reset RCC clock configuration to the default reset state*/
	HAL_RCC_DeInit();


	/* Update the SystemCoreClock variable*/
	SystemCoreClockUpdate();

	uartDevConfig(&uartDev, &huart2, uartRxBuffer, uartTxBuffer, 0);
	i2cHardwareSetup();
	spiDevConfig(&spiDev, &hspi1, spiRxBuffer, spiTxBuffer, 0);

	/* Create 2 task with the same priority */
	//xTaskCreate(vTaskHandler, "Task 1", configMINIMAL_STACK_SIZE, (void *)"Hello From task 1\r\n", 1, &xTaskHandle1);

	//xTaskCreate(vTaskHandler, "Send string", configMINIMAL_STACK_SIZE, (void *)"Hello From task 2\r\n", 2, &xTaskHandle2);

	xTaskCreate(vUartCmdTaskHandler, "Command handler", 500, NULL, 2, &xuartTaskHandle);
	xTaskCreate(vLedTaskHandler, "LED Task", 500, NULL, 2, &xledTaskHandle);


	//xTaskCreate(vLedTaskHandler, "LED Task", configMINIMAL_STACK_SIZE, (void *)"500", 1, NULL);

	/* Start the scheduler: This function will never return */
	vTaskStartScheduler();

	for(;;);
}


void vLedTaskHandler(void *params){

	TickType_t xDelayMs = 0;

	// Select the LED delay depending on the task type
	switch(taskType)
	{
	case TEMPERATURE_TASK:
		xDelayMs = pdMS_TO_TICKS(ledDelay);
		break;
	case ACCELEROMETER_TASK:
		xDelayMs = pdMS_TO_TICKS(ledDelay);
		break;
	default:
		xDelayMs = pdMS_TO_TICKS(50);
	}


	while(1)
	{
		// Start toggleling if notification comes from uart task
		if(notify)
		{
			HAL_GPIO_TogglePin(GPIOA, LED5_PIN);
			vTaskDelay(ledDelay);
		}
	}
}

void vAccTaskHandler(void *params)
{
	while(1)
	{

	}
}

void vTempTaskHandler(void *params)
{
	while(1)
	{

	}
}


void vUartCmdTaskHandler(void *params)
{
	while(1)
	{
		vUartHandleCmd(&uartDev);
	}
}


void vUartHandleCmd(UartDev_T *uartDev)
{
	if(uartDev->uartRxFlag == UART_RX_CMP)
	{
		if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_GET_TEMP], uartDev->size)) == 0)
		{
			// Call Temperature task
			// Blink LED 1/2 second
			ledDelay = LED_DELAY_500_MS;
			notify = 1;
			taskType = TEMPERATURE_TASK;
			xTaskNotify(xledTaskHandle, 0, eNoAction);

		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_GET_ACC], uartDev->size)) == 0)
		{
			// Call accelerometer
			// Print angle every 2 seconds
			// Turn LED every 1 second
			ledDelay = LED_DELAY_1_S;
			notify = 1;
			taskType = ACCELEROMETER_TASK;
			xTaskNotify(xledTaskHandle, 0, eNoAction);

		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_3_ON], uartDev->size)) == 0)
		{
			// Torn on LED
			HAL_GPIO_WritePin(GPIOA, LED3_PIN, GPIO_PIN_SET);
			notify = 0;
			taskType = DEFAULT_TASK;
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_3_OFF], uartDev->size)) == 0)
		{
			// Turn off led
			HAL_GPIO_WritePin(GPIOA, LED3_PIN, GPIO_PIN_RESET);
			notify = 0;
			taskType = DEFAULT_TASK;
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_4_ON], uartDev->size)) == 0)
		{
			// Torn on LED
			HAL_GPIO_WritePin(GPIOA, LED4_PIN, GPIO_PIN_SET);
			notify = 0;
			taskType = DEFAULT_TASK;
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_4_OFF], uartDev->size)) == 0)
		{
			// Turn off led
			HAL_GPIO_WritePin(GPIOA, LED4_PIN, GPIO_PIN_RESET);
			notify = 0;
			taskType = DEFAULT_TASK;
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_5_ON], uartDev->size)) == 0)
		{
			// Torn on LED
			HAL_GPIO_WritePin(GPIOA, LED5_PIN, GPIO_PIN_SET);
			notify = 0;
			taskType = DEFAULT_TASK;
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_5_OFF], uartDev->size)) == 0)
		{
			// Turn off led
			HAL_GPIO_WritePin(GPIOA, LED5_PIN, GPIO_PIN_RESET);
			notify = 0;
			taskType = DEFAULT_TASK;
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_6_ON], uartDev->size)) == 0)
		{
			// Torn on LED
			HAL_GPIO_WritePin(GPIOA, LED6_PIN, GPIO_PIN_SET);
			notify = 0;
			taskType = DEFAULT_TASK;
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_6_OFF], uartDev->size)) == 0)
		{
			// Turn off led
			HAL_GPIO_WritePin(GPIOA, LED6_PIN, GPIO_PIN_RESET);
			notify = 0;
			taskType = DEFAULT_TASK;
		}
		else
		{
			// Report invalid command
			uartSendStr(uartDev, (uint8_t *)"Invalid CMD\r\n", strlen((const char*)"Invalid CMD\r\n"));
			notify = 0;
			taskType = DEFAULT_TASK;
		}
		// Reset the flag
		uartDev->uartRxFlag = UART_NO_RX;
		memErase(uartDev->uartRxBuffer, uartDev->size);
	}
}

void rtosDelay(uint16_t delay)
{
	uint16_t currentDelay = xTaskGetTickCount();
	// Get the tick value corresponding to the delay in ms
	uint16_t delayInTick = (currentDelay * configTICK_RATE_HZ )/1000;
	while(xTaskGetTickCount() < (currentDelay + delayInTick));
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
