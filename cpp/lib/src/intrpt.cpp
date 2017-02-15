#include "intrpt.h"



Intrpt::Intrpt(Gpio::Port p , uint8_t pi, sense s)
:pin_ (p, pi, Gpio::PP::NoPP)
{
	EXTI->IMR |= 1 << pi;
	SYSCFG->EXTICR[0] |= static_cast<uint8_t> (p) << (4*pi);
	EXTI->RTSR |= (((static_cast<uint8_t> (s)&0xF0)>>4) << pi);
	EXTI->FTSR |= ((static_cast<uint8_t> (s)&0x0F) << pi);
	NVIC_EnableIRQ (EXTI0_1_IRQn);
}

