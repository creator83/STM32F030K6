#include "qenc.h"


Qenc::data::data (uint16_t h, uint16_t l, uint16_t v, data * n)
:high(h), low(l), value (v), next(n)
{
 
}


Qenc::Qenc (uint16_t range)
:pha (QdDef::PhaPort, QdDef::PhaPin, QdDef::PhaAf),
phb (QdDef::PhbPort, QdDef::PhbPin, QdDef::PhbAf), count(0)
{
 
	//high = range << 2;
	ptrTimer = TIM1;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	setMode ();
 first = last = nullptr;
 current = first;
}

Qenc::Qenc (Gtimer &t, uint16_t range)
:pha (QdDef::PhaPort, QdDef::PhaPin, QdDef::PhaAf),
phb (QdDef::PhbPort, QdDef::PhbPin, QdDef::PhbAf)
{
	gtimer = &t;
	//high = range << 2;
	ptrTimer = gtimer->getPtrTimer();
	setMode ();
 first = last = nullptr;
 current = first;
}

Qenc::Qenc (Atimer &t, uint16_t range)
:pha (QdDef::PhaPort, QdDef::PhaPin, QdDef::PhaAf),
phb (QdDef::PhbPort, QdDef::PhbPin, QdDef::PhbAf)
{
	atimer = &t;
	//high = range << 2;
	ptrTimer = TIM1;
	setMode ();
  first = last = nullptr;
 current = first;
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
 if (current->value == 0 && ptrTimer->CNT == 0xFFFF)
 {
   current->value = 0;
   ptrTimer->CNT = 0;
 }
 else if (current->value == current->high&& ptrTimer->CNT >= current->high+4)
 {
   current->value = current->high;
   ptrTimer->CNT = current->high;
 }
 else 
 {
   current->value = ptrTimer->CNT;
 }
}

uint16_t Qenc::getValue ()
{
  return current->value >> 2;
}

void Qenc::addDataSet (uint16_t h, uint16_t l)
{
  data * nData = new data (h, l);
  if (last == nullptr)
  {
   first = nData;
  }
  else
  {
   last->next = nData;
  }
  last = nData;
  ++count;
}

void Qenc::nextSet ()
{
 if (current->next==nullptr)
  current = first;
 else
  current = current->next;
}

void Qenc::setValue  (uint16_t val)
{
	current->value = val << 2;
	ptrTimer->CNT = current->value;
}

void Qenc::start ()
{
	ptrTimer->CR1 |= TIM_CR1_CEN;
}

void Qenc::stop ()
{
	ptrTimer->CR1 &= ~TIM_CR1_CEN;
}

