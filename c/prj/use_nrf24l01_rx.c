#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "delay.h"
#include "segled.h"
#include "nrf24l01.h"


#define F_CPU 48000000
#define tick 1000
#define systick_ms 1
#define systick_val (F_CPU/tick)*systick_ms
#define button_ 1

uint8_t stat;


void EXTI4_15_IRQHandler(void)
{
	uint8_t data, reg_val;
	EXTI->PR |= 1 << IRQ;
	reg_val = nrf24l01_read_register (STATUS);
	nrf24l01_write_register (STATUS, reg_val);
	if (reg_val&(1 << RX_DR)) data = nrf24l01_read_register (R_RX_PAYLOAD);
	segled_buffer (data);
}


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


int main ()
{
	segled_init ();
	SysTick_Config (systick_val);
	nrf24l01_init();
	
	segled_buffer (nrf24l01_read_register(CONFIG));
	//uint8_t nrf24l01_sc_bit (unsigned char reg,unsigned char register_bit,char W);
	
		
	//buffer (6523);
	while (1)
	{
		delay_ms (2000);
		nrf24l01_RX_mode ();
		segled_buffer (nrf24l01_read_register(CONFIG));
	}
	
	
}

