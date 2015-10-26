#include "stm32f0xx.h"                  // Device header
#include "uart.h"
#include "max6675.h"
#include "tact.h"

extern char buff [4];


int main ()
{
	uint8_t i;
	init_HSI ();
	init_PLL ();
	uart_init ();
	max6675_init ();
	
	
	while (1)
	{
		buffer (readCelsius());
		transmit_string ("==");
		for (i=0;i<4;++i)
		{
			transmit_byte (buff[i]);
		}
		delay_ms (500);
	}
	
}

