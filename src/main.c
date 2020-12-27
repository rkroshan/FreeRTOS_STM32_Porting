/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

#define TASK1_PRIORITY 2			//remember task priority can never be 0 as idle task priority is 0
#define TASK2_PRIORITY 2

TaskHandle_t xTask1_Handle = NULL;
TaskHandle_t xTask2_Handle = NULL;

void vTask1_Handler(void* params);
void vTask2_Handler(void* params);

int main(void)
{
	//By default the system clk is running at max speed which 168Mhz
	//this is done by setsysclk function
	//if it is not required then deinit the clk config and set it to desired value using functions provided in stm32f4xx_rcc.c
	RCC_DeInit();
	//set HSE as default clk
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
	//call the systemcoreclk update function the SystemCoreClock variable to newly set clk frequency
	SystemCoreClockUpdate();

	//create 1st task
	xTaskCreate(vTask1_Handler, "Led_1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, &xTask1_Handle);
	xTaskCreate(vTask2_Handler, "Led_2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, &xTask2_Handle);

	//start the FreeRtos Task Scheduler
	vTaskStartScheduler();


	for(;;);
}

void vTask1_Handler(void* params)
{
	//task must never return
	while(1){};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(NULL); //NULL means the task itself or can call the vtask1_handler
}
void vTask2_Handler(void* params)
{
	//task must never return
	while(1){};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(xTask2_Handle); //NULL means the task itself
}
