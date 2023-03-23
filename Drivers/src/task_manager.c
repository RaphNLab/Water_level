#include "task_manager.h"

uint16_t ledDelay = 0;
uint8_t notifyAcc = 0;
uint8_t notifyTemp = 0;

Bool_T accTimerFlag = FALSE;
Bool_T tempTimerFlag = FALSE;

Bool_T taskEnablefFlag = TRUE;

const TickType_t tempTaskDelay = 10000 / portTICK_PERIOD_MS;
const TickType_t accTaskDelay = 2000 / portTICK_PERIOD_MS;

TaskHandle_t xledTaskHandle = NULL;
TaskHandle_t xuartTaskHandle = NULL;
TaskHandle_t xaccTaskHandle = NULL;
TaskHandle_t xtempTaskHandle = NULL;

TaskHandle_t xtimerTaskHandle = NULL;
TimerHandle_t xAccTimerHandle = NULL;
TimerHandle_t xTempTimerHandle = NULL;

TaskType_T taskType = DEFAULT_TASK;


void vLedTaskHandler(void *params)
{
	while(1)
	{
		// Start toggleling if notification comes from uart task
		if(notifyAcc || notifyTemp)
		{
			HAL_GPIO_TogglePin(GPIOA, LED5_PIN);
			vTaskDelay(ledDelay);
		}
	}
}

/* This function handle the watermeter task command*/
void vAccTaskHandler(void *params)
{
	uint16_t accXAxis = 0;
	uint16_t accYAxis = 0;
	uint16_t accZAxis = 0;

	while(1)
	{
		if(notifyAcc)
		{
			if(accTimerFlag)
			{
				MPU9250GetAccAxis(&accXAxis, &accYAxis, &accZAxis);
				pPrintf("MPU9250 Accelerometer X Axis: %d \n", accXAxis);
				pPrintf("MPU9250 Accelerometer Y Axis: %d \n", accYAxis);
				pPrintf("MPU9250 Accelerometer Z Axis: %d \n", accZAxis);
			}
			accTimerFlag = FALSE;
		}
	}
}

/* callback to notify timer overflow
 * When the 2s are reached
 * */
void accTaskCallback(TimerHandle_t xTimer)
{
	accTimerFlag = TRUE;
}

/* This function handle the temperature task command*/
void vTempTaskHandler(void *params)
{
	float temperature = 0.0;

	while(1)
	{
		if(notifyTemp)
		{
			if(tempTimerFlag)
			{
				//devAddr = MPU9250WhoAmI();
				MPU9250GetTemp(&temperature);
				pPrintf("MPU9250 Temperature: %d°C\n", (uint8_t)temperature);
				//pPrintf("MPU9250 ADDR: 0x%X\n", (uint8_t)devAddr);
			}

			tempTimerFlag = FALSE;
		}
	}
}

/* callback to notify timer overflow
 * When the 10s are reached
 * */
void tempTaskCallback(TimerHandle_t xTimer)
{
	tempTimerFlag = TRUE;
}


/* Handles incoming commands over uart */
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
		if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_GET_TEMP], strlen(uartCmdList[AT_GET_TEMP]))) == 0)
		{
			// Call Temperature task
			// Blink LED 1/2 second
			if(taskEnablefFlag)
			{
				ledDelay = LED_DELAY_500_MS;
				notifyTemp = 1;
				vTaskSuspend(xaccTaskHandle);
				vTaskResume(xtempTaskHandle);
				taskType = TEMPERATURE_TASK;
			}
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_GET_ACC], strlen(uartCmdList[AT_GET_ACC]))) == 0)
		{
			// Call accelerometer
			// Print angle every 2 seconds
			// Turn LED every 1 second
			if(taskEnablefFlag)
			{
				ledDelay = LED_DELAY_1_S;
				notifyAcc = 1;
				vTaskSuspend(xtempTaskHandle);
				vTaskResume(xaccTaskHandle);
				taskType = ACCELEROMETER_TASK;
			}
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_3_ON], strlen(uartCmdList[AT_LED_3_ON]))) == 0)
		{
			// Torn on LED
			if(taskEnablefFlag)
			{
				HAL_GPIO_WritePin(GPIOA, LED3_PIN, GPIO_PIN_SET);
				notifyAcc = 0;
				notifyTemp = 0;
				taskType = DEFAULT_TASK;
			}
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_3_OFF], strlen(uartCmdList[AT_LED_3_ON]))) == 0)
		{
			// Turn off led
			if(taskEnablefFlag)
			{
				HAL_GPIO_WritePin(GPIOA, LED3_PIN, GPIO_PIN_RESET);
				notifyAcc = 0;
				notifyTemp = 0;
				taskType = DEFAULT_TASK;
			}
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_4_ON], strlen(uartCmdList[AT_LED_4_ON]))) == 0)
		{
			// Torn on LED
			if(taskEnablefFlag)
			{
				HAL_GPIO_WritePin(GPIOA, LED4_PIN, GPIO_PIN_SET);
				notifyAcc = 0;
				notifyTemp = 0;
				taskType = DEFAULT_TASK;
			}
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_4_OFF], strlen(uartCmdList[AT_LED_4_ON]))) == 0)
		{
			// Turn off led
			if(taskEnablefFlag)
			{
				HAL_GPIO_WritePin(GPIOA, LED4_PIN, GPIO_PIN_RESET);
				notifyAcc = 0;
				notifyTemp = 0;
				taskType = DEFAULT_TASK;
			}
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_5_ON], strlen(uartCmdList[AT_LED_5_ON]))) == 0)
		{
			// Torn on LED
			if(taskEnablefFlag)
			{
				HAL_GPIO_WritePin(GPIOA, LED5_PIN, GPIO_PIN_SET);
				notifyAcc = 0;
				notifyTemp = 0;
				taskType = DEFAULT_TASK;
			}
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_5_OFF], strlen(uartCmdList[AT_LED_5_ON]))) == 0)
		{
			// Turn off led
			if(taskEnablefFlag)
			{
				HAL_GPIO_WritePin(GPIOA, LED5_PIN, GPIO_PIN_RESET);
				notifyAcc = 0;
				notifyTemp = 0;
				taskType = DEFAULT_TASK;
			}
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_6_ON], strlen(uartCmdList[AT_LED_6_OFF]))) == 0)
		{
			// Torn on LED
			if(taskEnablefFlag)
			{
				HAL_GPIO_WritePin(GPIOA, LED6_PIN, GPIO_PIN_SET);
				notifyAcc = 0;
				notifyTemp = 0;
				taskType = DEFAULT_TASK;
			}
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_LED_6_OFF], strlen(uartCmdList[AT_LED_6_OFF]))) == 0)
		{
			// Turn off led
			if(taskEnablefFlag)
			{
				HAL_GPIO_WritePin(GPIOA, LED6_PIN, GPIO_PIN_RESET);
				notifyAcc = 0;
				notifyTemp = 0;
				taskType = DEFAULT_TASK;
			}
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_STOP], strlen(uartCmdList[AT_STOP]))) == 0)
		{
			// Suspend all Task not the uart task to monitor incoming command
			taskEnablefFlag = FALSE;
			vTaskSuspend(xledTaskHandle);
			vTaskSuspend(xtempTaskHandle);
			vTaskSuspend(xaccTaskHandle);

			HAL_GPIO_WritePin(GPIOA, LED6_PIN, GPIO_PIN_RESET);

			notifyAcc = 0;
			notifyTemp = 0;
			taskType = DEFAULT_TASK;
		}
		else if((strncasecmp((const char*)uartDev->uartRxBuffer, (const char*)uartCmdList[AT_START], strlen(uartCmdList[AT_START]))) == 0)
		{
			taskEnablefFlag = TRUE;
			//Resume all other task
			vTaskResume(xledTaskHandle);
			vTaskResume(xtempTaskHandle);
			vTaskResume(xaccTaskHandle);

			// Turn off led
			HAL_GPIO_WritePin(GPIOA, LED6_PIN, GPIO_PIN_RESET);
			notifyAcc = 0;
			notifyTemp = 0;
			taskType = DEFAULT_TASK;
		}
		else
		{
			// Report invalid command
			uartSendStr(uartDev, (uint8_t *)"Invalid CMD\r\n", strlen((const char*)"Invalid CMD\r\n"));
			notifyAcc = 0;
			notifyTemp = 0;
			taskType = DEFAULT_TASK;
		}
		// Reset the flag
		uartDev->uartRxFlag = UART_NO_RX;
		memErase(uartDev->uartRxBuffer, uartDev->size);
	}
}
