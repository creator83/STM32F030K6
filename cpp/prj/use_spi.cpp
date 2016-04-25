#include "stm32f0xx.h"
#include "gpio.h"
#include "delay.h"
#include "tact.h"
#include "spi.h"


tact frq;

spi spi1 (spi::A, spi::div128);
Gpio A (Gpio::A);

const char frac = 0;
const char ones = 1;
const char dec = 2;

 /* 
  extern "C"
  {
    void EXTI0_1_IRQHandler();
  }*/

int main()
{
	
	A.setOutPin (frac);
	A.setOutPin (ones);
	A.setOutPin (dec);
	A.setPin (frac);

  while (1)
  {

		spi1.Clear_CS();
		spi1.transmit (0x0F);
		spi1.Set_CS();
		delay_ms (100);
		spi1.Clear_CS();
		spi1.transmit (0xF0);
		spi1.Set_CS();
		delay_ms (100);
  }
}
