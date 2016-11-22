#include "intrpt.h"



Intrpt::Intrpt(Gpio::Port p , uint8_t pi, sense s)
:pin_ (p, pi, Gpio::NoPP)
{
	EXTI->IMR |= 1 << pi;
	SYSCFG->EXTICR[0] |= p << (4*pi);
	switch (static_cast <uint8_t> (s))
	{
		case 1:
			EXTI->RTSR |= 1 << pi;
		break;
		case 2:
			EXTI->FTSR |= 1 << pi;
		break;
		case 3:
			EXTI->RTSR |= 1 << pi;
			EXTI->FTSR |= 1 << pi;
		break;
	}
	NVIC_EnableIRQ (EXTI0_1_IRQn);
}

