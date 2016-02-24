#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "segled.h"
#include "systimer.h"
 
tact frq;

segled indicator (segled::A);

Gpio button (Gpio::A);
Gpio triac (Gpio::A);

const char b = 6;
const char t = 3;

uint16_t N = 628;
uint16_t P;

void TIM14_init ();

struct flags
{
	unsigned led_indicator_delay : 1;
}flag;


struct butt_flag
{
	unsigned prev_state : 1;
	unsigned curr_state : 1;
	unsigned counter    : 6;
}butt, encoder;

extern "C"
{
	void SysTick_Handler ();
	void TIM14_IRQHandler ();
}


void SysTick_Handler ()
{
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}
	if (!(button.PinState(b)))
	{
		butt.curr_state = 1;
	}
	else
	{
		butt.curr_state = 1;
	}
}

void TIM14_IRQHandler ()
{
	TIM14->SR &= ~TIM_SR_UIF;
	if (P>0)
	{
		--P;
	}
	else
	{
		TIM14->CR1 &= ~TIM_CR1_CEN;
		//сбросить флаг кнопки
		P=N;
	}
}



int main()
{
	button.setInPin (b);
	triac.setOutPin (t);
	P=N;
	indicator.get_buffer (N);
	systimer sys(systimer::ms, 1);
	//TIM14_init ();
	
	//TIM14->CR1 |= TIM_CR1_CEN;
  while (1)
  {

  }
}

void TIM14_init ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN ;
	TIM14->PSC = tact::get_frq()*1000 - 1;
	TIM14->ARR = 100;
	TIM14->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM14_IRQn);
}


