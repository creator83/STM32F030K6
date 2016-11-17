#include "uart.h"


Uart::Uart (baud b)
:tx (UartDef::TxPort, UartDef::TxPin, UartDef::TxAf),
rx (UartDef::RxPort, UartDef::RxPin, UartDef::RxAf)
{
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

  //settings UART
  USART1->CR1 |= (USART_CR1_RE|USART_CR1_TE);
  
  USART1->BRR |= (Tact::get_frq()*1000000/b);
  USART1->CR1 |= USART_CR1_UE;
}

void Uart::transmit (uint8_t data)
{
  while (!(USART1->ISR&USART_ISR_TXE));
  USART1->TDR = data;
}

void Uart::transmit (char * str)
{
  while (*str)
  {
    while (!(USART1->ISR&USART_ISR_TXE));
    USART1->TDR = *str++;
  }
}
