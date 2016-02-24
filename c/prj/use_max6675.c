#include "stm32f0xx.h"                  // Device header
#include "uart.h"
#include "max6675.h"
#include "tact.h"
#include "delay.h"
#include "segled.h"



#define F_CPU 48000000
#define tick 1000
#define systick_ms 1
#define systick_val (F_CPU/tick)*systick_ms
#define button_ 1


char n [10] = {'0','1','2','3','4','5','6','7','8','9'};
char buf [2];

void buffer1 (uint16_t t);
/*
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

void init_buttons(void)
{
	button.last_state = button.current_state = 0;
	button.min_press = 20;
	button.max_press = 1000;
}

*/
int main ()
{
	uint8_t i;
	uart_init ();
	max6675_init ();
	//segled_init ();
	//SysTick_Config (systick_val);

	
	
	
	//buffer (6523);
	while (1)
	{
	
		buffer1 (readCelsius());
		//segled_buffer (readCelsius());
		/*delay_ms (500);
		if (button.short_press)
		{
			// foo();
			button.short_press = 0;
		}*/
		//===Send to Uart===//
	//	segled_buffer (readCelsius());
		transmit_string ("==");

		for (i=0;i>2;++i)
		{
			transmit_byte (n [buf[i]]);
		}
		transmit_byte ('C');
		delay_ms (500);
	}
	
}

void buffer1 (uint16_t t)
{
	char d, o;
	uint16_t temp = t;
	
	for (d=0;temp>=10;++d)temp -=10;

	for (o=0;temp>=1;++o)temp--;
	
	buf [1] = d;
	buf [0] = o;
}

