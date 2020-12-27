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
#define TASK3_PRIORITY 2
#define TASK4_PRIORITY 2

TaskHandle_t xTask1_Handle = NULL;
TaskHandle_t xTask2_Handle = NULL;
TaskHandle_t xTask3_Handle = NULL;
TaskHandle_t xTask4_Handle = NULL;

void vTask1_Handler(void* params);
void vTask2_Handler(void* params);
void vTask3_Handler(void* params);
void vTask4_Handler(void* params);

void Init_GPIO_LED(void);

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

	//create  task
	xTaskCreate(vTask1_Handler, "Led_1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, &xTask1_Handle);
	xTaskCreate(vTask2_Handler, "Led_2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, &xTask2_Handle);
	xTaskCreate(vTask3_Handler, "Led_3", configMINIMAL_STACK_SIZE, NULL, TASK3_PRIORITY, &xTask3_Handle);
	xTaskCreate(vTask4_Handler, "Led_4", configMINIMAL_STACK_SIZE, NULL, TASK4_PRIORITY, &xTask4_Handle);

	//init the LED GPIO
	Init_GPIO_LED();
	//start the FreeRtos Task Scheduler
	vTaskStartScheduler();


	for(;;);
}

void vTask1_Handler(void* params) //this will toggle pin 15 led
{
	//task must never return
	while(1){
		GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
		vTaskDelay(500);
		taskYIELD();
	};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(NULL); //NULL means the task itself or can call the vtask1_handler
}
void vTask2_Handler(void* params) //this will toggle pin 14 led
{
	//task must never return
	while(1){
		GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		vTaskDelay(500);
		taskYIELD(); //leave the mcpu and get in task ready state in the queue at last in same priority task lists
	};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(xTask2_Handle); //NULL means the task itself
}

void vTask3_Handler(void* params) //this will toggle pin 13 led
{
	//task must never return
	while(1){
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
		vTaskDelay(500);
		taskYIELD();
	};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(xTask3_Handle); //NULL means the task itself
}

void vTask4_Handler(void* params) //this will toggle pin 13 led
{
	//task must never return
	while(1){
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		vTaskDelay(500);
		taskYIELD();
	};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(xTask4_Handle); //NULL means the task itself
}


void Init_GPIO_LED(void)
{
		//Init GPIOD Peripheral
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		GPIO_InitTypeDef gpio_led;
		gpio_led.GPIO_Mode = GPIO_Mode_OUT;
		gpio_led.GPIO_OType = GPIO_OType_PP;
		gpio_led.GPIO_PuPd = GPIO_PuPd_UP;
		gpio_led.GPIO_Pin = GPIO_Pin_15; //blue led
		GPIO_Init(GPIOD, &gpio_led);

		gpio_led.GPIO_Pin = GPIO_Pin_14; //red led
		GPIO_Init(GPIOD, &gpio_led);

		gpio_led.GPIO_Pin = GPIO_Pin_13; //orange led
		GPIO_Init(GPIOD, &gpio_led);

		gpio_led.GPIO_Pin = GPIO_Pin_12; //green led
		GPIO_Init(GPIOD, &gpio_led);
}

