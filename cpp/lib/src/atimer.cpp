#include "atimer.h"



Atimer::Atimer ( uint16_t divider)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	setPsc (divider);
}

Atimer::Atimer (uint16_t divider, uint16_t arr)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	setPsc (divider);
	setArr (arr);
}

Atimer::Atimer ()
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
}

void Atimer::setCnt (uint16_t val)
{
	TIM1->CNT = val;
}

void Atimer::setPsc (uint16_t p)
{
	TIM1->PSC = p-1;
}

void Atimer::setArr (uint16_t a)
{
	TIM1->ARR = a;
}

void Atimer::setChannelValue (uint16_t val)
{
	TIM1->CCR1 |= val << (ch_*16);
}

uint16_t Atimer::getCnt ()
{
	return TIM1->CNT;
}

void Atimer::start ()
{
	TIM1->CR1 |= TIM_CR1_CEN;
}

void Atimer::stop ()
{
	TIM1->CR1 &= ~TIM_CR1_CEN;
}

void Atimer::clearTif()
{
	TIM1->SR &= ~ TIM_SR_TIF;
}

void Atimer::clearUif()
{
	TIM1->SR &= ~ TIM_SR_UIF;
}


