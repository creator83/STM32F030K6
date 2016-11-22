#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "spi.h"
#include "nrf24l01.h"


Tact frq;
Spi spi0;
Nrf24l01 radio (spi0);

  extern "C"
  {
    void EXTI0_1_IRQHandler(void);
		
  }
	
void EXTI0_1_IRQHandler()
{
	
	EXTI->PR |= 1 << nrf24Def::irqPin;
	
		
}

int main()
{
	radio.readRegister (CONFIG);
	radio.comm (FLUSH_TX);
	radio.readStatus ();

	
  while (1)
  {
		uint8_t st = radio.readStatus ();
		if (st>15) radio.writeRegister (STATUS, st);
		radio.sendByte (25);
		delay_ms (2000);
		radio.readRegister (CONFIG);
		
		/*for (uint8_t i=0;i<0xFF;++i)
		{
			radio.sendByte (i);
			
			delay_ms (500);
		}*/
	
  }
}

