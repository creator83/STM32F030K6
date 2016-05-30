#include "general_timer.h"


uint32_t general_timer::bases [5] = {TIM3_BASE, TIM14_BASE, TIM15_BASE, TIM16_BASE, TIM17_BASE};
uint8_t general_timer::intrpt [5] = {TIM3_IRQn, TIM14_IRQn, TIM15_IRQn, TIM16_IRQn, TIM17_IRQn};
PotMemFn general_timer::init [5] = {&general_timer::timer3_init, &general_timer::timer14_init,&general_timer::timer15_init,&general_timer::timer16_init,&general_timer::timer17_init};

general_timer::general_timer (timers t, uint16_t psc, uint16_t arr)
{
	tmr = t;
	(this->*(general_timer::init[tmr]))();
	((TIM_TypeDef *) bases [tmr])->PSC = psc;
	((TIM_TypeDef *) bases [tmr])->ARR = arr;	
}

void general_timer::timer3_init ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

}

void general_timer::timer14_init ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
}

void general_timer::timer15_init ()
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
}

void general_timer::timer16_init ()
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
}

void general_timer::timer17_init ()
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
}




