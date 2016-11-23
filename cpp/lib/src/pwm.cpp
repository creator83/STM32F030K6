#include "pwm.h"

Pwm::PtrPwm Pwm::funcMode [3] ={&Pwm::setEdgePwm};
uint8_t Pwm::ccrPtr [4] = {13, 14, 15, 16};

Pwm::Pwm (Gtimer &t, Gpio::Port p, uint8_t pin, Gpio::Afmode af, Gtimer::nChannel ch, mode mode_, pulseMode m, inverse i)
:pwmPin (p, pin, af)
{
	timer = &t;
	ptrTimer = timer->getPtrTimer();
	pwmChannel = ch;
	timer->stop ();
	
	(this->*(Pwm::funcMode[mode_]))(m);
}

Pwm::Pwm (Atimer &t, Gpio::Port p, uint8_t pin, Gpio::Afmode af, Gtimer::nChannel ch, mode mode_, pulseMode m, inverse i)
:pwmPin (p, pin, af)
{
	timer1 = &t;
	ptrTimer = TIM1;
	pwmChannel = ch;
	timer->stop ();
	
	(this->*(Pwm::funcMode[mode_]))(m);
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
