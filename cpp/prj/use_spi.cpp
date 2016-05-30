#include "stm32f0xx.h"
#include "gpio.h"
#include "delay.h"
#include "tact.h"
#include "spi.h"


tact frq;

spi spi1 (spi::A, spi::div128);




 /* 
  extern "C"
  {
    void EXTI0_1_IRQHandler();
  }*/

void transfer_byte (uint8_t data );

int main()
{
	
  while (1)
  {

		transfer_byte (0x0F);
		delay_ms (500);
		transfer_byte (0xF0);
		delay_ms (500);
  }
}


void transfer_byte (uint8_t data )
{
	spi1.Clear_CS ();
	spi1.put_data (data);
	while (spi1.flag_bsy());
	spi1.Set_CS ();
}
