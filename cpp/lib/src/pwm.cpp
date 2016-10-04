#include "pwm.h"


Pwm::Pwm (nTimer n_, nChannel ch, mode m, pulseMode m_, inverse i)
:Gtimer (n_)
{
	//N channel output
	timerBase [n_]->CCER |= 1 << (ch*4);
	timerBase [n_]->CCER &= ~ (1 << ((ch*4)+1));
	timerBase [n_]->CCER &= ~ (m_ << ((ch*4)+1));
	
	timerBase [n_]->CCMR1 &= ~ (7 << ((ch*8)+4));
	timerBase [n_]->CCMR1 |= (i << ((ch*8)+4));
	//settings pin
	pin.settingPinPort(PwmDef::PwmPort);
	pin.settingPin (PwmDef::PwmPin, Gpio::AltFunc);
	pin.settingAf (PwmDef::PwmPin, PwmDef::PwmAlt);
}

