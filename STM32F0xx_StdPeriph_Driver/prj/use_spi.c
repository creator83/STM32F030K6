#include "stm32f0xx.h"                  // Device header
#include "delay.h"
#include "spi.h"


int main ()
{
	spi1_init ();
	while (1)
	{
		transfer_byte (0xF0);
		delay_ms (500);
		transfer_byte (0x0F);
		delay_ms (500);
	}
}
