#include "uart.h"


uart::uart (baud b)
{
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  
  //===setting pin===//
	//TX
	Tx.settingPinPort (UartDef::TxPort);
	Tx.settingPin (UartDef::TxPin, Gpio::AltFunc);
	Tx.settingAf (UartDef::TxPin, UartDef::TxAf);
	
	//RX
	Rx.settingPinPort (UartDef::RxPort);
	Rx.settingPin (UartDef::RxPin, Gpio::AltFunc);
	Rx.settingAf (UartDef::RxPin, UartDef::RxAf);
  
  //settings UART
  USART1->CR1 |= (USART_CR1_RE|USART_CR1_TE);
  
  USART1->BRR |= (tact::get_frq()*1000000/b);
  USART1->CR1 |= USART_CR1_UE;
}

void uart::transmit (uint8_t data)
{
  while (!(USART1->ISR&USART_ISR_TXE));
  USART1->TDR = data;
}

void uart::transmit (char * str)
{
  while (*str)
  {
    while (!(USART1->ISR&USART_ISR_TXE));
    USART1->TDR = *str++;
  }
}
