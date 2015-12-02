#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "spi.h"
#include "delay.h"



int main ()
{
	init_spi_8 ();

	while(1)
	{
		CS_CLEAR;
		spi1_tx_8 (0xF0);
		CS_SET;
		delay_ms (500);
		CS_CLEAR;
		spi1_tx_8 (0x0F);
		CS_SET;
		delay_ms (500);
	}

}
