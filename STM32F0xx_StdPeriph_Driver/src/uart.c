#include "uart.h"

void Usart0_init (void)
{
	GPIO_InitTypeDef Gpio_Usart0;
	USART_InitTypeDef usart_i;
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA, ENABLE);
	Gpio_Usart0.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	Gpio_Usart0.GPIO_Mode = GPIO_Mode_AF;
	Gpio_Usart0.GPIO_Speed = GPIO_Speed_Level_3;
	Gpio_Usart0.GPIO_OType = GPIO_OType_PP;
	Gpio_Usart0.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init (GPIOA, &Gpio_Usart0);	
	GPIO_PinAFConfig (GPIOA, GPIO_PinSource9,GPIO_AF_1);
	GPIO_PinAFConfig (GPIOA, GPIO_PinSource10,GPIO_AF_1);
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1, ENABLE);
	usart_i.USART_BaudRate = BAUD;
	usart_i.USART_HardwareFlowControl =  USART_HardwareFlowControl_None;
	usart_i.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	usart_i.USART_Parity = USART_Parity_No ;
	usart_i.USART_StopBits = USART_StopBits_1;
	usart_i.USART_WordLength = USART_WordLength_8b;
	USART_Init (USART1, &usart_i);
	USART_Cmd (USART1, ENABLE);
}

void transmit_byte (uint8_t data)
{
	while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
	USART_SendData (USART1, data);
}

void transmit_string (char * str)
{
	while (*str)
	{
		while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
		USART_SendData (USART1, *str);
		++str;
	}	
}
