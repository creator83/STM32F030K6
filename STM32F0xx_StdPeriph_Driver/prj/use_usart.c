#include "stm32f0xx.h"                  // Device header
#include "delay.h"
#include "uart.h"


int main ()
{
	
	//SysTick_Config (SystemCoreClock/1000);
	Usart0_init ();

	while (1)
	{
		transmit_string ("Hello");
		delay_ms (1000);
	}
}
