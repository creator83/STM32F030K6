#include "stm32f0xx.h"                  // Device header
//#include "uart.h"
#include "max6675.h"
#include "tact.h"
#include "delay.h"
#include "segled.h"

int main ()
{
	init_HSI ();
	init_PLL ();
	//uart_init ();
	max6675_init ();
	segled_init ();
	
	//buffer (6523);
	while (1)
	{
		buffer (readCelsius());
		delay_ms (500);

		/*//===Send to Uart===//
		buffer (readCelsius());
		transmit_string ("==");
		transmit_string (buff);
		transmit_byte ('C');
		delay_ms (500);*/
	}
	
}

