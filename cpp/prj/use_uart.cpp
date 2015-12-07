#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "uart.h"


int main()
{
  tact frq;
  uart uart1 (uart::baud9600);
  
  while (1)
  {
    /*
    for (uint8_t i=0;i<20;++i)
    {
      uart1.transmit (i);
      delay_ms (500);
    }
    
    for (uint8_t i=20;i>0;--i)
    {
      uart1.transmit (i);
      delay_ms (500);
    }*/
    uart1.transmit ("====Hello===== ");
    delay_ms (1000);
    uart1.transmit ("Its STM32F030 BABY :-)))");
    delay_ms (1000);
    uart1.transmit ("Русишш");
    delay_ms (1000);    
    
  }
}