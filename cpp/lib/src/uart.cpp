#include "uart.h"


uart::uart (baud b)
:pin (Gpio::A)
{
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  
  //настройка выхода
  pin.setOutPin (TX , Gpio::AltFunc , Gpio::High);
  
  //настройка входа
  
  pin.setOutPin (RX , Gpio::AltFunc , Gpio::High , Gpio::OpenDrain);
  
  //
  GPIOA->AFR[1] |= (1 << 4|1 << 8);
  
  //настройка UART
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
    USART1->TDR = *str;
    str++;
  }
}
