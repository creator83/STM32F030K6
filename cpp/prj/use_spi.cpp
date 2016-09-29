#include "stm32f0xx.h"
#include "gpio.h"
#include "delay.h"
#include "tact.h"
#include "spi.h"
#include "shift_registr.h"

tact frq;





 /* 
  extern "C"
  {
    void EXTI0_1_IRQHandler();
  }*/


int main()
{
	Spi spi1 (Spi::master, Spi::hardware);
	Shift reg (spi1);
	
  while (1)
  {
		reg.send (0x0F);
		delay_ms (500);
		reg.send (0xF0);
		delay_ms (500);		
  }
}

