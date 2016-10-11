#include "qenc.h"




Qenc::Qenc (uint16_t range)
:Gtimer (Gtimer::Timer3)
{
	high = range << 2;
	setMode ();
}


void Qenc::setMode ()
{
	//===Setings pin===//
	//pha
	pha.settingPinPort(QdDef::PhaPort);
	pha.settingPin(QdDef::PhaPin, Gpio::AltFunc);
	pha.settingAf (QdDef::PhaPin, QdDef::PhaAf);
	pha.settingPP (QdDef::PhaPin, Gpio::PullUp);
	//phb
	pha.settingPinPort(QdDef::PhbPort);
	pha.settingPin(QdDef::PhbPin, Gpio::AltFunc);
	pha.settingAf (QdDef::PhbPin, QdDef::PhbAf);
	pha.settingPP (QdDef::PhbPin, Gpio::PullUp);

	//===Settings timer===//
	
	timerBase [n_]->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
	timerBase [n_]->CCMR1 |= TIM_CCMR1_IC1F_1| TIM_CCMR1_IC2F_1;
	timerBase [n_]->CCER &= ~(TIM_CCER_CC1P|TIM_CCER_CC2P);
	timerBase [n_]->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	start ();
}

uint16_t Qenc::getValue ()
{
	value = timerBase [n_]->CNT;
	if (value>high)
	{
		value = high;
		timerBase [n_]->CNT = high;
		return value >> 2;
	}		
	return value >> 2;
}

