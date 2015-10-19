#include "stm32f0xx.h"  
#include "Gpio.h"
#include "tact.h"
#include "hc_sr04.h"
#include "uart.h"


tact frq;
const uint8_t trig = 2;
const uint8_t echo = 0;
const uint8_t start = 1;
const uint8_t stop = 0;

uint8_t takt;

	uart uart0 (uart::baud9600);
	hc_sr04 sense (hc_sr04::A , trig, echo);	

	
extern "C"
{
	void EXTI0_1_IRQHandler(void);
}

void EXTI0_1_IRQHandler(void)
{
	EXTI->PR |= 1 << echo;
	if (!(GPIOA->IDR & (1 << echo)))
	{
		sense.StartStop (start);
	}
	else
	{
		takt = sense.StartStop (stop)/58;
	}
}

int main ()
{

		while (1)
	{
		sense.Get_val ();
		//uart0.transmit (takt >>8);
		uart0.transmit (takt);
		delay_ms (1000);
		
	}
}