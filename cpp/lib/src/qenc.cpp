#include "qenc.h"




Qenc::Qenc (uint16_t range)
:pha (QdDef::PhaPort, QdDef::PhaPin, QdDef::PhaAf),
phb (QdDef::PhbPort, QdDef::PhbPin, QdDef::PhbAf), low(0)
{
	high = range << 2;
	ptrTimer = TIM1;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	setMode ();
}

Qenc::Qenc (Gtimer &t, uint16_t range)
:pha (QdDef::PhaPort, QdDef::PhaPin, QdDef::PhaAf),
phb (QdDef::PhbPort, QdDef::PhbPin, QdDef::PhbAf), low(0)
{
	gtimer = &t;
	high = range << 2;
	ptrTimer = gtimer->getPtrTimer();
	setMode ();
}

Qenc::Qenc (Atimer &t, uint16_t range)
:pha (QdDef::PhaPort, QdDef::PhaPin, QdDef::PhaAf),
phb (QdDef::PhbPort, QdDef::PhbPin, QdDef::PhbAf), low(0)
{
	atimer = &t;
	high = range << 2;
	ptrTimer = TIM1;
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

void Qenc::scan ()
{
 if (value == 0 && ptrTimer->CNT == 0xFFFF)
 {
   value = 0;
   ptrTimer->CNT = 0;
 }
 else if (value == high&& ptrTimer->CNT >= high+4)
 {
   value = high;
   ptrTimer->CNT = high;
 }
 else 
 {
   value = ptrTimer->CNT;
 }
}

uint16_t Qenc::getValue ()
{
  return value >> 2;
}

void Qenc::setValue  (uint16_t val)
{
	value = val << 2;
	ptrTimer->CNT = value;
}

void Qenc::start ()
{
	ptrTimer->CR1 |= TIM_CR1_CEN;
}

void Qenc::stop ()
{
	ptrTimer->CR1 &= ~TIM_CR1_CEN;
}

