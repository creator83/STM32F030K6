#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "segled.h"
#include "systimer.h"

tact frq;
segled indicator (segled::A, segled::A);
Gpio B (Gpio::B);

const char pin = 0;

struct flags
{
	unsigned led_indicator_delay : 1;
}flag;



extern "C"
{
	void SysTick_Handler ();
}


void SysTick_Handler ()
{
	static uint16_t i,k=0;
	static uint8_t j=0;
	
	if(j>3)j=0;
	if (k>=1000)
	{
		B.ChangePinState (pin);
		k=0;
	}		
	else	++k;
	if (i>=1000)
	{
		indicator.frame(j);
		i=0;
	}
	else ++i;
	++j;
	/*
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}*/

}



int main()
{
  systimer (systimer::ms, 1);
	B.setOutPin (pin);
	indicator.get_buffer (5632);
  while (1)
  {
		/*
		delay_ms (500);
		if (button.short_press)*/
		{
			// foo();
			//button.short_press = 0;
		}
  }
}
