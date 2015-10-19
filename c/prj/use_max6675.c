#include "stm32f0xx.h"                  // Device header
#include "uart.h"
#include "max6675.h"
#include "tact.h"




int main ()
{
	init_HSI ();
	init_PLL ();
	uart_init ();
	max6675_init ();
	
	
	while (1)
	{
		transmit_byte (readCelsius());
		delay_ms (500);
	}
	
}

