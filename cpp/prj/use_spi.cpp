#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "Spi.h"
#include "segled.h"
 
tact frq;
const char led = 1;
 /* 
  extern "C"
  {
    void EXTI0_1_IRQHandler();
  }*/

char number [13] = {0x3F ,0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D, 0x07 , 0x7F , 0x6F ,  0x00, 0x60, 0x6A};
int main()
{
	spi spi1 (spi::A, spi::div256);
	Gpio digit (Gpio::A);
	digit.setOutPort (0x07);
	digit.setValPort (0x07);
	
	/*spi1.Clear_CS();
	spi1.transmit (0x03);
	spi1.Set_CS();*/
  while (1)
  {
		for (uint8_t i=0;i<13;++i)
		{
			spi1.Clear_CS();
			spi1.transmit (number [i]);
			spi1.Set_CS();
			delay_ms (1000);			
		}/*
		spi1.Clear_CS();
		spi1.transmit (0x0F);
		spi1.Set_CS();
		delay_ms (1000);
		spi1.Clear_CS();
		spi1.transmit (0xF0);
		spi1.Set_CS();
		delay_ms (1000);*/
  }
}
