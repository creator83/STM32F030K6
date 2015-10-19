#include "uart.h"
#include "delay.h"



void uart_init ()
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	
	//Settings pins
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//TX
	GPIOA->MODER |= GPIO_MODER_MODER9_1;
	GPIOA->AFR[1] |= 1 << 4;
	
	//RX
	GPIOA->MODER |= GPIO_MODER_MODER10_1;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR1;
	GPIOA->AFR[1] |= 1 << 8;
	
	//Settings UART
	USART1->CR1 |= (USART_CR1_RE|USART_CR1_TE);
	USART1->BRR = 0;
	USART1->BRR = BRR_VAL;
	USART1->CR1 |= USART_CR1_UE;
}		

void transmit_byte (uint8_t data)
{
	while (!(USART1->ISR&USART_ISR_TXE)) {};
  USART1->TDR = data;
}

void transmit_string (char * str)
{
  while (*str)
  {
    while (!(USART1->ISR&USART_ISR_TXE));
    USART1->TDR = *str;
    str++;
  }
}
