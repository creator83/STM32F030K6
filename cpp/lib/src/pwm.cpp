#include "pwm.h"

Pwm::PtrPwm Pwm::funcMode [3] ={&Pwm::setEdgePwm};
uint8_t Pwm::ccrPtr [4] = {13, 14, 15, 16};

Pwm::Pwm (Gtimer &t, Pin &p, Gtimer::nChannel ch, mode mode_, pulseMode m, inverse i)
:pwmPin (&p), timer(&t)
{
	
	ptrTimer = timer->getPtrTimer();
	pwmChannel = static_cast <uint8_t>(ch);
	timer->stop ();
	
	(this->*(Pwm::funcMode[static_cast <uint8_t>(mode_)]))(m);
}

Pwm::Pwm (Atimer &t,  Pin &p, Gpio::Afmode af, Gtimer::nChannel ch, mode mode_, pulseMode m, inverse i)
:pwmPin (&p), timer1(&t)
{
	ptrTimer = TIM1;
	pwmChannel = static_cast <uint8_t>(ch);
	timer->stop ();
	
	(this->*(Pwm::funcMode[static_cast <uint8_t>(mode_)]))(m);
}
void Pwm::setEdgePwm (pulseMode m)
{
	//settings timer
	ptrTimer->CCER &= ~ (1 << ((pwmChannel*4)+1));
	ptrTimer->CCER |=  (static_cast <uint8_t>(m) << ((pwmChannel*4)+1))|(1 << (pwmChannel*4));
	
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

void Pwm::setPeriod (uint16_t val)
{
	timer->getPtrTimer()->ARR = val;
}

void Pwm::start ()
{
	timer->start();
}

void Pwm::stop ()
{
	timer->stop ();
}
