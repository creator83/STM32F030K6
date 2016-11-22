#include "qenc.h"




Qenc::Qenc (uint16_t range)
:pha (QdDef::PhaPort, QdDef::PhaPin, QdDef::PhaAf),
phb (QdDef::PhbPort, QdDef::PhbPin, QdDef::PhbAf)
{
	high = range << 2;
	ptrTimer = TIM1;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	setMode ();
}

Qenc::Qenc (Gtimer &t, uint16_t range)
:pha (QdDef::PhaPort, QdDef::PhaPin, QdDef::PhaAf),
phb (QdDef::PhbPort, QdDef::PhbPin, QdDef::PhbAf)
{
	timer = &t;
	high = range << 2;
	ptrTimer = timer->getPtrTimer();
	setMode ();
}

void Qenc::setMode ()
{
	//===Settings timer===//
	
	ptrTimer->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
	ptrTimer->CCMR1 |= TIM_CCMR1_IC1F_1| TIM_CCMR1_IC2F_1;
	ptrTimer->CCER &= ~(TIM_CCER_CC1P|TIM_CCER_CC2P);
	ptrTimer->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	ptrTimer->CR1 |= TIM_CR1_CEN;
}

uint16_t Qenc::getValue ()
{
	value = ptrTimer->CNT;
	return value >> 2;
}

void Qenc::setValue  (uint16_t val)
{
	value = val << 2;
	ptrTimer->CNT = value;
}

