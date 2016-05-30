#include "general_timer.h"


uint32_t general_timer::bases [5] = {TIM3_BASE, TIM14_BASE, TIM15_BASE, TIM16_BASE, TIM17_BASE};
uint8_t general_timer::intrpt [5] = {TIM3_IRQn, TIM14_IRQn, TIM15_IRQn, TIM16_IRQn, TIM17_IRQn};
PotMemFn general_timer::init [5] = {&general_timer::timer3_init, &general_timer::timer14_init,&general_timer::timer15_init,&general_timer::timer16_init,&general_timer::timer17_init};

general_timer::general_timer (uint8_t t)
{
	tmr = t;
	(this->*(general_timer::init[tmr]))();	
}

general_timer::general_timer (timers t)
{
	tmr = t;
	(this->*(general_timer::init[tmr]))();	
}

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

void general_timer::output_mode ()
{
	((TIM_TypeDef *) bases [tmr])->DIER |= TIM_DIER_UIE;	
}

void general_timer::set_interrupt (int8_t pr)
{
	NVIC_EnableIRQ (static_cast <IRQn> (intrpt [tmr]));
	NVIC_SetPriority(static_cast <IRQn> (intrpt [tmr]), pr);
}

void general_timer::Set_CNT (uint16_t cnt)
{
	((TIM_TypeDef *) bases [tmr])->CNT = cnt;
}
	
void general_timer::Set_PSC (uint16_t psc)
{
	((TIM_TypeDef *) bases [tmr])->PSC = psc;
}

void general_timer::Set_ARR (uint16_t arr)
{
	((TIM_TypeDef *) bases [tmr])->ARR = arr;
}

uint16_t general_timer::Get_CNT ()
{
	return ((TIM_TypeDef *) bases [tmr])->CNT;
}

void general_timer::Start ()
{
	((TIM_TypeDef *) bases [tmr])->CR1 |= TIM_CR1_CEN;
}

void general_timer::Stop ()
{
	((TIM_TypeDef *) bases [tmr])->CR1 &= ~TIM_CR1_CEN;
}
