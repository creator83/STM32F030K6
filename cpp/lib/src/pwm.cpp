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
	ptrTimer->CCER |= 1 << (pwmChannel*4);
	ptrTimer->CCER &= ~ (1 << ((pwmChannel*4)+1));
	ptrTimer->CCER &= ~ (m << ((pwmChannel*4)+1));
	ptrTimer->CCMR1 &= ~ (7 << ((pwmChannel*8)+4));
	ptrTimer->CCMR1 |= (i << ((pwmChannel*8)+4));
}

void Pwm::setValue (uint16_t val)
{
	timer->setChannelValue (val);
}

void Pwm::start ()
{
	timer->start();
}

void Pwm::stop ()
{
	timer->stop ();
}
