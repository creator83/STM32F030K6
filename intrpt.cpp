#include "intrpt.h"



intrpt::intrpt(Port p , uint8_t pin_, sense s)
:pin (p)
{
	pin.setInPin (pin_);
	EXTI->IMR |= 1 << pin_;
	SYSCFG->EXTICR[0] |= p << (4*pin_);
	switch (static_cast <uint8_t> (s))
	{
		case 1:
			EXTI->RTSR |= 1 << pin_;
		break;
		case 2:
			EXTI->FTSR |= 1 << pin_;
		break;
		case 3:
			EXTI->RTSR |= 1 << pin_;
			EXTI->FTSR |= 1 << pin_;
		break;
	}
}

intrpt::intrpt(uint8_t p , uint8_t pin_, sense s)
:pin (p)
{
	pin.setInPin (pin_);
	EXTI->IMR |= 1 << pin_;
	SYSCFG->EXTICR[0] |= p << (4*pin_);
	switch (static_cast <uint8_t> (s))
	{
		case 1:
			EXTI->RTSR |= 1 << pin_;
		break;
		case 2:
			EXTI->FTSR |= 1 << pin_;
		break;
		case 3:
			EXTI->RTSR |= 1 << pin_;
			EXTI->FTSR |= 1 << pin_;
		break;
	}
}
