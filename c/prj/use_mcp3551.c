#include "stm32f0xx.h"   
#include "mcp3551.h"
#include "tact.h"
#include "delay.h"
#include "segled.h"

#define F_CPU 48000000
#define tick 1000
#define systick_ms 1
#define systick_val (F_CPU/tick)*systick_ms
#define button_ 1

struct flags
{
	unsigned led_indicator_delay : 1;
}flag;

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

void SysTick_Handler (void)
{
	//increment button's and encoder's counters 
	if (!(button.long_press||button.short_press))button.counter++;
	
	encoder.counter++;
	
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		led_number();
		flag.led_indicator_delay = 1;
	}
	//Cheking press button
	button.current_state = !(GPIOA->IDR&1 << button_);
	
	if (!(button.last_state&&button.current_state))button.counter = 0;;
	button.last_state = button.current_state;
	
	if (button.counter>button.min_press) button.short_press = 1;
}


int main ()
{
	segled_init ();
	SysTick_Config (systick_val);
	mcp3551_init ();
	
	
	while (1)
	{
		segled_buffer (mcp3551_getTemp(getCode()));
		delay_ms (500);
		if (button.short_press)
		{
			// foo();
			button.short_press = 0;
		}
	}
	
}
