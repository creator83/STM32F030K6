#include "timer14.h"

/*timer14::timer14 (uint16_t prsk )
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	TIM14->PSC = prsk-1;
	
}*/

timer14::timer14 (uint16_t val, mode m)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	switch (static_cast <uint8_t> (m))
	{
		case 0: 
			TIM14->PSC |= tact::get_frq() - 1;
			TIM14->ARR = val;
		break;
		case 1:
			TIM14->PSC |= tact::get_frq()*1000 - 1;
			TIM14->ARR = val;
		break;
		case 3:
			TIM14->PSC |= val;
		break;		
	}
}
/*
timer14::timer14 (uint16_t us)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	TIM14->PSC |= tact::get_frq() - 1;
	TIM14->ARR = us;
}
*/

void timer14::Set_CNT (uint16_t cnt)
{
	TIM14->CNT = cnt;
}

uint16_t timer14::Get_CNT ()
{
	return TIM14->CNT;
}

void timer14::Set_ARR (uint16_t arr)
{
	TIM14->ARR = arr;
}

void timer14::interrupt (intrpt i)
{
	TIM14->DIER |= 1 << i;		
	NVIC_EnableIRQ(TIM14_IRQn);
}

void timer14::Start ()
{
	TIM14->CR1 |= TIM_CR1_CEN;
}

void timer14::Stop ()
{
	TIM14->CR1 &= ~TIM_CR1_CEN;
}

void timer14::ClearFlag()
{
	TIM14->SR &= ~TIM_SR_UIF;
}
