#include "uart.h"
#include "mcp3551.h"
#include "tact.h"
#include "delay.h"

extern char buff [4];


int main ()
{
	init_HSI ();
	init_PLL ();
	uart_init ();
	mcp3551_init ();
	
	
	while (1)
	{
		mcp3551_buffer (mcp3551_getTemp(getCode()));
		transmit_string ("==");
		transmit_string (buff);
		transmit_byte ('C');
		delay_ms (500);

	}
	
}
