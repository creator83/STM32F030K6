#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "spi.h"
#include "nrf24l01.h"


Tact frq;
Spi spi0;

  extern "C"
  {
    void EXTI0_1_IRQHandler();
		
  }
	
void EXTI0_1_IRQHandler()
{
	EXTI->PR |= 1 << 1;
}

int main()
{
	Nrf24l01 radio (spi0);
	radio.readRegister (CONFIG);
	radio.comm (FLUSH_TX);
	radio.readStatus ();
	radio.sendByte (1);
	
  while (1)
  {
		/*for (uint8_t i=0;i<0xFF;++i)
		{
			radio.sendByte (i);
			
			delay_ms (500);
		}*/
	
  }
}

