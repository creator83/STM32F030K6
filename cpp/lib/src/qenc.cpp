#include "qenc.h"




Qenc::Qenc (uint16_t range)
:pha (QdDef::PhaPort, QdDef::PhaPin, QdDef::PhaAf),
phb (QdDef::PhbPort, QdDef::PhbPin, QdDef::PhbAf)
{
	high = range << 2;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	setMode ();
}


void Qenc::setMode ()
{
	//===Settings timer===//
	
	TIM1->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
	TIM1->CCMR1 |= TIM_CCMR1_IC1F_1| TIM_CCMR1_IC2F_1;
	TIM1->CCER &= ~(TIM_CCER_CC1P|TIM_CCER_CC2P);
	TIM1->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	TIM1->CR1 |= TIM_CR1_CEN;
}

uint16_t Qenc::getValue ()
{
	value = TIM1->CNT;
	return value >> 2;
}

void Qenc::setValue  (uint16_t val)
{
	value = val << 2;
	TIM1->CNT = value;
}

