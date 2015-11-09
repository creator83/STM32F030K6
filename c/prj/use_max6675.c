#include "stm32f0xx.h"                  // Device header
//#include "uart.h"
#include "max6675.h"
#include "tact.h"
#include "delay.h"

extern char max6675_buff [4];


int main ()
{
	init_HSI ();
	init_PLL ();
	//uart_init ();
	max6675_init ();
	
	
	while (1)
	{
		max6675_buffer(readCelsius());
		
		/*
		buffer (readCelsius());
		transmit_string ("==");
		transmit_string (buff);
		transmit_byte ('C');
		delay_ms (500);*/
	}
	
}

