#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "segled.h"
#include "systimer.h"


struct buttons
{
	unsigned counter :16;
	unsigned current_state :1;
	unsigned last_state :1;
	unsigned min_press :6; 
	unsigned max_press :16;
	unsigned long_press :1;
	unsigned short_press :1; 
}button, encoder;

struct flags
{
	unsigned led_indicator_delay : 1;
}flag;

const uint8_t button_ = 1;

extern "C"
{
void SysTick_Handler (void);
}
tact frq;
segled indicator (segled::B, segled::A);

void SysTick_Handler (void)
{
	//increment button's and encoder's counters 
	if (!(button.long_press||button.short_press))button.counter++;
	
	encoder.counter++;
	
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}
	//Cheking press button
	button.current_state = !(GPIOA->IDR&1 << button_);
	
	if (!(button.last_state&&button.current_state))button.counter = 0;;
	button.last_state = button.current_state;
	
	if (button.counter>button.min_press) button.short_press = 1;
}



int main()
{
  systimer (systimer::ms, 1);
	
	
  while (1)
  {
		indicator.get_buffer (5632);
		delay_ms (500);
		if (button.short_press)
		{
			// foo();
			button.short_press = 0;
		}
  }
}
