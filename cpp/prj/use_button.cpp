#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "systimer.h"
#include "segled.h"
#include "button.h"


tact frq;
Gpio A (Gpio::A);
Gpio B (Gpio::B);


segled indicator (segled::A);

char number [13] = {0x3F ,0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D, 0x07 , 0x7F , 0x6F ,  0x00, 0x60, 0x6A};
char numberDp [13] = {0xBF , 0x86 , 0xDB , 0xCF , 0xE6 , 0xED , 0xFD , 0x87 , 0xFF , 0xEF , 0x00, 0x60, 0x6A};


void scan_enc ();

const char btn = 6 ;
const char enc_button = 6 ;
const char triac = 3;
const char encA = 9 ;
const char encB = 10;

button button1 (button::A, btn);

struct encdr
{
	uint8_t state;
	uint16_t count;
}encod;



uint16_t N = 62;

void TIM14_init ();
void TIM3_init ();

struct flags
{
	unsigned led_indicator_delay : 1;
	unsigned off :1;
}flag;




void short_press ();
void long_press ();
extern "C"
{
	void SysTick_Handler ();
	void TIM14_IRQHandler ();
	void TIM17_IRQHandler ();
	void TIM3_IRQHandler ();
	void TIM16_IRQHandler ();
}


void SysTick_Handler ()
{
	if (flag.off) ;
	else
	{
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}
	}
}
  
void TIM3_IRQHandler ()
{
	TIM3->SR &= ~TIM_SR_UIF;
	if (button1.short_press) button1.action_short (short_press);

}

void TIM17_IRQHandler ()
{
	TIM17->SR &= ~TIM_SR_UIF;
	static uint8_t i = N;
	if (i)
	{
		i--;
		indicator.get_buffer (i);
		A.setPin (triac);
	}
	else 
	{
		i = N;
		TIM17->CR1 &= ~TIM_CR1_CEN;
		A.clearPin (triac);	
		indicator.get_buffer (N+(encod.count>>2));
	}
}

void TIM14_IRQHandler ()
{
	TIM14->SR &= ~TIM_SR_UIF;
	button1.scan_short();	
}

void TIM17_init ();


int main()
{
	indicator.get_buffer (N);
	A.setOutPin (triac);
	A.setInPin (encA);
	A.setInPin (encB);
	B.setInPin (enc_button);
	
	systimer sys(systimer::ms, 1);
	NVIC_SetPriority(SysTick_IRQn, 0);
	TIM14_init ();
	TIM17_init ();
	TIM3_init ();
	
  while (1)
  {

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

void TIM17_init ()
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
	TIM17->PSC = tact::get_frq()*1000 - 1;
	TIM17->ARR = 100;
	TIM17->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM17_IRQn);
	NVIC_SetPriority(TIM17_IRQn, 2);
}

void TIM3_init ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC = tact::get_frq()*1000 - 1;
	TIM3->ARR = 1;
	TIM3->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM3_IRQn);
	NVIC_SetPriority(TIM3_IRQn, 2);
	TIM3->CR1 |= TIM_CR1_CEN;
}

void short_press ()
{
		TIM17->CR1 |= TIM_CR1_CEN;
}

