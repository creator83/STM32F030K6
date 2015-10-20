#include "stm32f0xx.h"                  // Device header


uint16_t delay;

void SysTick_Handler (void)
{
	if (delay > 0)delay--;
}

void delay_ms (uint16_t del)
{
	delay = del;
	while (delay);
}

void usart_init (void)
{
	GPIO_InitTypeDef Usart0;
	USART_InitTypeDef usart_i;
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA, ENABLE);
	Usart0.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	Usart0.GPIO_Mode = GPIO_Mode_AF;
	Usart0.GPIO_Speed = GPIO_Speed_Level_3;
	Usart0.GPIO_OType = GPIO_OType_PP;
	Usart0.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init (GPIOA, &Usart0);	
	GPIO_PinAFConfig (GPIOA, GPIO_PinSource9,GPIO_AF_1);
	GPIO_PinAFConfig (GPIOA, GPIO_PinSource10,GPIO_AF_1);
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1, ENABLE);
	usart_i.USART_BaudRate = 9600;
	usart_i.USART_HardwareFlowControl =  USART_HardwareFlowControl_None;
	usart_i.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	usart_i.USART_Parity = USART_Parity_No ;
	usart_i.USART_StopBits = USART_StopBits_1;
	usart_i.USART_WordLength = USART_WordLength_8b;
	USART_Init (USART1, &usart_i);
	USART_Cmd (USART1, ENABLE);
}

void send_str (char * str)
{
	while (*str)
	{
		while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
		USART_SendData (USART1, *str);
		++str;
	}
}

int main ()
{
	
	SysTick_Config (SystemCoreClock/1000);
	usart_init ();

	while (1)
	{
		send_str ("Hello");
		delay_ms (1000);
				
	}
}
