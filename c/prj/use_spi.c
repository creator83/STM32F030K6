#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "spi.h"
#include "delay.h"



int main ()
{
	init_HSI ();
	init_PLL ();
	init_spi ();

	while(1)
	{
		clear_cs ();
		transfer (0xF0);
		set_cs ();
		delay_ms (500);
		clear_cs ();
		transfer (0x0F);
		set_cs ();
		delay_ms (500);
	}

}