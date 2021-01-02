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
#include "queue.h"
#include "timers.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

TaskHandle_t Handle_menu_display_task = NULL;
TaskHandle_t Handle_cmd_handling_task = NULL;
TaskHandle_t Handle_cmd_processing_task = NULL;
TaskHandle_t Handle_uart_write_task = NULL;

//task handles
void menu_display_task(void* params);
void cmd_handling_task(void* params);
void cmd_processing_task(void* params);
void uart_write_task(void* params);

//Queue handles
QueueHandle_t command_queue=NULL, uart_queue=NULL;

void Init_GPIO_LED(void);
void Init_UART(void);
void printmsg(char* msg);
void rtos_delayms(uint32_t delay_ms);

uint8_t getCommandCode(uint8_t* buffer);
void getArguments(uint8_t* data);

void make_led_on(void);
void make_led_off(void);
void make_led_toggle_start(uint32_t toggle_delay);
void make_led_toggle_stop(void);
void make_led_status_read(char* data);
void make_rtc_datetime_read(char* data);
void make_exit_app(void);
void print_errormsg(char* data);

char menu[] = "\r\nFreeRTOS APPLICATION can perform Below Functions \r\n"
			"(1) LED_ON\r\n"
			"(2) LED_OFF\r\n"
			"(3) LED_TOGGLE_START\r\n"
			"(4) LED_TOGGLE_STOP\r\n"
			"(5) LED_STATUS_READ\r\n"
			"(6) RTC_DATETIME_READ\r\n"
			"(0) EXIT APP\r\n"
			"\r\nPlease Enter the task number which needs to be performed\r\n"
			":";

#define LED_ON				1
#define LED_OFF				2
#define LED_TOGGLE_START	3
#define LED_TOGGLE_STOP		4
#define LED_STATUS_READ		5
#define RTC_DATETIME_READ	6
#define EXIT_APP			0

typedef struct APP_CMD{
	uint8_t CMD;
	uint8_t CMD_ARGS[10];
}APP_CMD_t;

uint8_t command_len=0;
uint8_t command_buffer[20];
TimerHandle_t Timer_LedToggle = NULL;

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

	//create queues
	command_queue = xQueueCreate(10,sizeof(APP_CMD_t*));
	uart_queue = xQueueCreate(10,sizeof(char*));

	if((command_queue != NULL && uart_queue != NULL)){
		//create  task
		xTaskCreate(menu_display_task, "MENU_DISP", configMINIMAL_STACK_SIZE, NULL, 1, &Handle_menu_display_task);
		xTaskCreate(cmd_handling_task, "CMD_HANDLE", configMINIMAL_STACK_SIZE, NULL, 2, &Handle_cmd_handling_task);
		xTaskCreate(cmd_processing_task, "CMD_PROCESS", configMINIMAL_STACK_SIZE, NULL, 2, &Handle_cmd_processing_task);
		xTaskCreate(uart_write_task, "UART_WRITE", configMINIMAL_STACK_SIZE, NULL, 2, &Handle_uart_write_task);

		//start the FreeRtos Task Scheduler
		vTaskStartScheduler();

	}else{
		printmsg("Failed To create queues\r\n");
	}


	for(;;);
}

void menu_display_task(void* params) //this will toggle pin 15 led
{
	char* pdata = menu;
	//task must never return
	while(1){
		xQueueSend(uart_queue,&pdata,portMAX_DELAY);

		//wait till someone notifies
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
	};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(NULL); //NULL means the task itself or can call the vtask1_handler
}
void cmd_handling_task(void* params) //this will toggle pin 14 led
{
	APP_CMD_t* new_cmd;
	uint8_t command_code=0;
	//task must never return
	while(1){

		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
		//send command to queue
		new_cmd = (APP_CMD_t*)pvPortMalloc(sizeof(APP_CMD_t));

		taskENTER_CRITICAL(); //it will disable all the interrupts having priority lower than max SYSCALL priority

			command_code  = getCommandCode(command_buffer);
			new_cmd->CMD = command_code;
			getArguments(new_cmd->CMD_ARGS);

		taskEXIT_CRITICAL();

		//send data to the queue
		xQueueSend(command_queue,&new_cmd,portMAX_DELAY);

	};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(NULL); //NULL means the task itself
}

void cmd_processing_task(void* params) //this will toggle pin 13 led
{
	APP_CMD_t* cmd;
	char task_msg[50];
	uint32_t toggle_delay = pdMS_TO_TICKS(600);
	//task must never return
	while(1){
		xQueueReceive(command_queue, (void *)&cmd, portMAX_DELAY);
		switch(cmd->CMD){
		case LED_ON:
			make_led_on();
			break;
		case LED_OFF:
			make_led_off();
			break;
		case LED_TOGGLE_START:
			make_led_toggle_start(toggle_delay);
			break;
		case LED_TOGGLE_STOP:
			make_led_toggle_stop();
			break;
		case LED_STATUS_READ:
			make_led_status_read(task_msg);
			break;
		case RTC_DATETIME_READ:
			make_rtc_datetime_read(task_msg);
			break;
		case EXIT_APP:
			make_exit_app();
			break;
		default:
			//cmd not found enable the menu printing
			print_errormsg(task_msg);
			xTaskNotify(Handle_menu_display_task,0,eNoAction);
			break;

		}

		//free the malloc memory created for storing cmd
		vPortFree(cmd);

	};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(NULL); //NULL means the task itself
}

void uart_write_task(void* params) //this will toggle pin 13 led
{
	char *Data = NULL;
	//task must never return
	while(1){
		xQueueReceive(uart_queue, &Data, portMAX_DELAY);
		printmsg(Data);
	};
	//if it returns anyhow or task work is complete it is not repeating then delete the task
	vTaskDelete(NULL); //NULL means the task itself
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

	//enable uart4 RXNE interrupt
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

	//NVIC UART4 priority
	NVIC_SetPriority(UART4_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1);

	//ENABLE NVIC INTERRUPT
	NVIC_EnableIRQ(UART4_IRQn);

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

void rtos_delayms(uint32_t delay_ms)
{
	vTaskDelay((delay_ms*configTICK_RATE_HZ)/1000);
}


void UART4_IRQHandler(void){

	uint8_t data_byte;
	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
	if(USART_GetFlagStatus(UART4, USART_FLAG_RXNE)){
		//yes we received some data
		data_byte = (uint8_t)USART_ReceiveData(UART4);
		command_buffer[command_len++] = data_byte;
		if(command_len >=(20-1)){
			command_len=0; //prevent the app from crashing
		}
		if(data_byte == '\r'){
			//reset the command len
			command_len = 0;
			//user finished entering command
			//notify command handle task
			xTaskNotifyFromISR(Handle_cmd_handling_task,0,eNoAction,&pxHigherPriorityTaskWoken);
			//notify menu print task as well
			xTaskNotifyFromISR(Handle_menu_display_task,0,eNoAction,&pxHigherPriorityTaskWoken);
		}
	}
	//if higher priority task woken up then task yield
	if(pxHigherPriorityTaskWoken){
		taskYIELD();
	}

}

uint8_t getCommandCode(uint8_t* buffer)
{
	return (buffer[0] - 48) ;
}

void getArguments(uint8_t* data)
{

}

void make_led_on(void)
{
	GPIO_SetBits(GPIOD, GPIO_Pin_14);
}
void make_led_off(void)
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_14);
}

void led_toggle(TimerHandle_t xTimer){
	GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
}
void make_led_toggle_start(uint32_t toggle_delay)
{
	if(Timer_LedToggle == NULL){
		//create the Software Timer
		Timer_LedToggle = xTimerCreate("LED_TOGGLE_TIMER", toggle_delay, pdTRUE, NULL, led_toggle);
	}
	//start the timer
	xTimerStart(Timer_LedToggle,portMAX_DELAY);

}
void make_led_toggle_stop(void)
{
	if(Timer_LedToggle != NULL){
		//stop the created timer
		xTimerStop(Timer_LedToggle,portMAX_DELAY);
	}
}
void make_led_status_read(char* data)
{
	sprintf(data, "\r\n LED STATUS is : %d\r\n", GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_14));
	xQueueSend(uart_queue,&data,portMAX_DELAY);
}
void make_rtc_datetime_read(char* data)
{
	RTC_DateTypeDef RTC_DateStruct;
	RTC_TimeTypeDef RTC_TimeStruct;

	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);

	sprintf(data,"\r\nYY:MM:DD = %02d:%02d:%02d\r\nHH:MM:SS = %02d:%02d:%02d",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,
			RTC_DateStruct.RTC_Date,RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds);

	xQueueSend(uart_queue,&data,portMAX_DELAY);
}

void make_exit_app(void)
{
	//delete all the tasks
	vTaskDelete(Handle_menu_display_task);
	vTaskDelete(Handle_uart_write_task);
	vTaskDelete(Handle_cmd_processing_task);
	vTaskDelete(Handle_cmd_handling_task);

	//disable all the interrupts or disable interrupts which you don't require
	NVIC_DisableIRQ(UART4_IRQn); //or use basepri assembly instructions to disable all interrupts portDISABLE_INTERRUPTS();

	//set the cpu in low power mode that will be done by idle hook function

}

void print_errormsg(char* data)
{
	sprintf(data, "\r\nCommand Not found\r\n");
	xQueueSend(uart_queue,&data,portMAX_DELAY);
}

void vApplicationIdleHook(void)
{
	//send the system in sleep mode
	__WFI();
}




