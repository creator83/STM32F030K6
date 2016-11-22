#include "intrpt.h"



Intrpt::Intrpt(Gpio::Port p , uint8_t pi, sense s)
:pin_ (p, pi, Gpio::NoPP)
{
	EXTI->IMR |= 1 << pi;
	SYSCFG->EXTICR[0] |= p << (4*pi);
	EXTI->RTSR |= (((s&0xF0)>>4) << pi);
	EXTI->FTSR |= ((s&0x0F) << pi);
	NVIC_EnableIRQ (EXTI0_1_IRQn);
}

