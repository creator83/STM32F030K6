#include "pwm.h"


Pwm::Pwm (Gtimer &t, Gpio::Port p, uint8_t pin, Gpio::Afmode af, Gtimer::nChannel ch, mode, pulseMode m, inverse i)
{
	timer = &t;
	ptrTimer = timer->getPtrTimer();
	pwmChannel = ch;
	timer->stop ();
	//Settings pins
	pwmPin.settingPinPort(p);
	pwmPin.settingPin (pin, Gpio::AltFunc);
	pwmPin.settingAf (pin, af);
	
	//settings timer
	ptrTimer->ARR = 1000;
	ptrTimer->CCER |= 1 << (pwmChannel*4);
	ptrTimer->CCER &= ~ (1 << ((pwmChannel*4)+1));
	ptrTimer->CCER |=  (m << ((pwmChannel*4)+1));
	ptrTimer->CCMR1 &= ~ (7 << ((pwmChannel*8)+4));
	ptrTimer->CCMR1 |= (i << ((pwmChannel*8)+4))|TIM_CCMR1_OC1PE;
	ptrTimer->EGR |= TIM_EGR_UG;
/*	TIM14->PSC = 47; 
  TIM14->ARR = 8; 
  TIM14->CCR1 = 4; 
  TIM14->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; 
  TIM14->CCER |= TIM_CCER_CC1E;
  TIM14->CR1 |= TIM_CR1_CEN; 
  TIM14->EGR |= TIM_EGR_UG; */
	
}

void Pwm::setValue (uint16_t val)
{
	ptrTimer->CCR1 = val;
}

void Pwm::start ()
{
	timer->start();
}

void Pwm::stop ()
{
	timer->stop ();
}
