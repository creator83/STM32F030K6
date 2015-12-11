#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "segled.h"
#include "systimer.h"
#include "mcp3551.h"

tact frq;
segled indicator (segled::A, segled::A);




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
		

	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}
	
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
	mcp3551 sensor;
	
  while (1)
  {
		sensor.getCode ();
		indicator.get_buffer (sensor.byteCode);
		delay_ms (500);
		/*if (button.short_press)*/
		{
			// foo();
			//button.short_press = 0;
		}
  }
}

