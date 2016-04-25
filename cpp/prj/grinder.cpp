#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "systimer.h"
#include "segled.h"

tact frq;
Gpio A (Gpio::A);

segled indicator (segled::A);

char number [13] = {0x3F ,0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D, 0x07 , 0x7F , 0x6F ,  0x00, 0x60, 0x6A};
char numberDp [13] = {0xBF , 0x86 , 0xDB , 0xCF , 0xE6 , 0xED , 0xFD , 0x87 , 0xFF , 0xEF , 0x00, 0x60, 0x6A};



const char button = 6 ;
const char triac = 3;
const char encA = 9 ;
const char encB = 10;



uint16_t N = 628;
uint16_t P;

void TIM14_init ();

struct flags
{
	unsigned led_indicator_delay : 1;
}flag;



	struct b_flags
{
	unsigned lmt_sh_press : 6;
	unsigned curr_state   : 1;
	unsigned count        : 7;
	unsigned sh_press     : 1;
	unsigned l_press      : 1;	
}button1;


extern "C"
{
	void SysTick_Handler ();
	void TIM14_IRQHandler ();
}

   /* */
void SysTick_Handler ()
{
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}
	
}
  

void TIM14_IRQHandler ()
{
	if (button1.curr_state)
	{
		
	}
	else
	{
		if (!A.PinState(button)) button1.curr_state = 1;
	}
	
	
	
}



int main()
{
	indicator.get_buffer (164);
	A.setOutPin (triac);
	A.setInPin (button);
	/*Gpio A (Gpio::A);

	
;*/

	systimer sys(systimer::ms, 1);
	TIM14_init ();

	
  while (1)
  {
		A.ChangePinState (triac);
		delay_ms (1000);
  }
}

void TIM14_init ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN ;
	TIM14->PSC = tact::get_frq()*1000 - 1;
	TIM14->ARR = 20;
	TIM14->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM14_IRQn);
	TIM14->CR1 |= TIM_CR1_CEN;
}


