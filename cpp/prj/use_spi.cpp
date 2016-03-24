#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "Spi.h"
#include "nrf24l01.h"
#include "uart.h"

tact frq;

 /* 
  extern "C"
  {
    void EXTI0_1_IRQHandler();
  }*/

int main()
{
	spi spi1 (spi::A, spi::div256);

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
