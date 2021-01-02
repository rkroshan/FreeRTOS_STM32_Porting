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
#include <string.h>
#include <stdint.h>

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
void Init_UART(void);
void printmsg(char* msg);

uint8_t isUartfree = 1;

int main(void)
{

	DWT->CTRL |= (1 << 0); //required by SEGGER to maintain timestamp information it enable to store cycle count information
	//By default the system clk is running at max speed which 168Mhz
	//this is done by setsysclk function
	//if it is not required then deinit the clk config and set it to desired value using functions provided in stm32f4xx_rcc.c
	RCC_DeInit();
	//set HSE as default clk
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
	//call the systemcoreclk update function the SystemCoreClock variable to newly set clk frequency
	SystemCoreClockUpdate();

	//setup extra peripherals
	//init the LED GPIO
	Init_GPIO_LED();
	Init_UART();

	//start SEGGER recording
	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();


	//create  task
	xTaskCreate(vTask1_Handler, "Led_1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, &xTask1_Handle);
	xTaskCreate(vTask2_Handler, "Led_2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, &xTask2_Handle);
	xTaskCreate(vTask3_Handler, "Led_3", configMINIMAL_STACK_SIZE, NULL, TASK3_PRIORITY, &xTask3_Handle);
	xTaskCreate(vTask4_Handler, "Led_4", configMINIMAL_STACK_SIZE, NULL, TASK4_PRIORITY, &xTask4_Handle);

	//start the FreeRtos Task Scheduler
	vTaskStartScheduler();


	for(;;);
}

void vTask1_Handler(void* params) //this will toggle pin 15 led
{
	//task must never return
	while(1){
		if(isUartfree == 1){
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
			printmsg("Hello world led1\r\n");
			vTaskDelay(50);
			isUartfree = 2;
			taskYIELD();
		}
	};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(NULL); //NULL means the task itself or can call the vtask1_handler
}
void vTask2_Handler(void* params) //this will toggle pin 14 led
{
	//task must never return
	while(1){
		if(isUartfree == 2){
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
			printmsg("Hello world led2\r\n");
			vTaskDelay(60);
			isUartfree = 3;
			taskYIELD(); //leave the mcpu and get in task ready state in the queue at last in same priority task lists
		}
	};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(xTask2_Handle); //NULL means the task itself
}

void vTask3_Handler(void* params) //this will toggle pin 13 led
{
	//task must never return
	while(1){
		if(isUartfree == 3){
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
			printmsg("Hello world led3\r\n");
			vTaskDelay(70);
			isUartfree = 4;
			taskYIELD();
		}
	};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(xTask3_Handle); //NULL means the task itself
}

void vTask4_Handler(void* params) //this will toggle pin 13 led
{
	//task must never return
	while(1){
		if(isUartfree == 4){
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			printmsg("Hello world led4\r\n");
			vTaskDelay(80);
			isUartfree = 1;
			taskYIELD();
		}
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

void Init_UART(void)
{
	//Init uart 4 peripheral clk
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	//pc10 tx :: pc11 rx
	//enable GPIOC peripheral port
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	//init the pins to alternate function mode
	GPIO_InitTypeDef gpio_uart4;
	memset(&gpio_uart4,0,sizeof(gpio_uart4));
	gpio_uart4.GPIO_Pin = GPIO_Pin_10;
	gpio_uart4.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart4.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &gpio_uart4);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);

	gpio_uart4.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC, &gpio_uart4);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);

	//uart init
	USART_InitTypeDef uart4_init;
	memset(&uart4_init,0,sizeof(uart4_init));
	uart4_init.USART_BaudRate = 115200;
	uart4_init.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx);
	uart4_init.USART_Parity = USART_Parity_No;
	uart4_init.USART_StopBits = USART_StopBits_1;
	uart4_init.USART_WordLength = USART_WordLength_8b;
	uart4_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(UART4, &uart4_init);

	//enable uart4 peripheral
	USART_Cmd(UART4, ENABLE);

}

void printmsg(char* msg)
{
	for(uint32_t i=0; i<strlen(msg); i++){
		while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) != SET); //wait until TXE is not 0
		USART_SendData(UART4, msg[i]);
	}
}


