#include "stm32f0xx.h"                  // Device header
#include "delay.h"
#include "uart.h"


int main ()
{
	
	//SysTick_Config (SystemCoreClock/1000);
	Usart0_init ();

	while (1)
	{
		transmit_string ("Hello, my Prend");
		delay_ms (1000);
		transmit_byte (0xFF);
		delay_ms (1000);
	}
}
