#include "pwm.h"

Pwm::PtrPwm Pwm::funcMode [3] ={&Pwm::setEdgePwm};
uint8_t Pwm::ccrPtr [4] = {13, 14, 15, 16};

Pwm::Pwm (Gtimer &t, Gpio::Port p, uint8_t pin, Gpio::Afmode af, Gtimer::nChannel ch, mode mode_, pulseMode m, inverse i)
{
	timer = &t;
	ptrTimer = timer->getPtrTimer();
	pwmChannel = ch;
	timer->stop ();
	//Settings pins
	pwmPin.settingPinPort(p);
	pwmPin.settingPin (pin, Gpio::AltFunc);
	pwmPin.settingAf (pin, af);
	
	(this->*(Pwm::funcMode[mode_]))(m);
	
/*	TIM14->PSC = 47; 
  TIM14->ARR = 8; 
  TIM14->CCR1 = 4; 
  TIM14->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; 
  TIM14->CCER |= TIM_CCER_CC1E;
  TIM14->CR1 |= TIM_CR1_CEN; 
  TIM14->EGR |= TIM_EGR_UG; */
	
}

void Pwm::setEdgePwm (pulseMode m)
{
	//settings timer
	ptrTimer->CCER &= ~ (1 << ((pwmChannel*4)+1));
	ptrTimer->CCER |=  (m << ((pwmChannel*4)+1))|(1 << (pwmChannel*4));
	
	ptrTimer->CCMR1 &= ~ (7 << ((pwmChannel*8)+4));
	ptrTimer->CCMR2 &= ~ (7 << ((pwmChannel*8)+4));
	if (pwmChannel<2) ptrTimer->CCMR1 |= (0x06 << ((pwmChannel*8)+4))|1 << ((pwmChannel*8)+3);
	else  ptrTimer->CCMR2 |= (0x06 << (((pwmChannel-2)*8)+4))|1 << ((pwmChannel*8)+3);
	
	ptrTimer->EGR |= TIM_EGR_UG;
}

void Pwm::setValue (uint16_t val)
{
	*(uint32_t*)((uint32_t*)timer->getPtrTimer()+ccrPtr[pwmChannel])= val; 
}

void Pwm::start ()
{
	timer->start();
}

void Pwm::stop ()
{
	timer->stop ();
}
