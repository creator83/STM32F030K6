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
	//phb
	pha.settingPinPort(QdDef::PhbPort);
	pha.settingPin(QdDef::PhbPin, Gpio::AltFunc);
	pha.settingAf (QdDef::PhbPin, QdDef::PhbAf);

	//===Settings timer===//
	TIM3->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0; /* (1)*/  
  //TIMx->CCER &= (uint16_t)(~(TIM_CCER_CC21 | TIM_CCER_CC2P); /* (2) */
  TIM3->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; /* (3) */
  TIM3->CR1 |= TIM_CR1_CEN;
	
	/*timerBase [n_]->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
	timerBase [n_]->CCER &= ~(TIM_CCER_CC1P|TIM_CCER_CC2P);
	timerBase [n_]->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	start ();*/
}

uint16_t Qenc::getValue ()
{
	value = timerBase [n_]->CNT;
	if (value>high)
	{
		value = high;
		timerBase [n_]->CNT = high;
	}
	return value >> 2;
}

