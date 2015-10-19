#include "stm32f0xx.h"  
#include "Gpio.h"
#include "tact.h"
#include "intrpt.h"

tact frq;
const uint8_t pin = 1; 
const uint8_t intr = 0; 

Gpio A (Gpio::A);

extern "C"
{
	void EXTI0_1_IRQHandler(void);
}

void EXTI0_1_IRQHandler(void)
{
	EXTI->PR |= 1 << intr;
	A.ChangePinState (pin);
	
}

int main ()
{
	
	
	A.setOutPin (pin);
	intrpt intA0 (intrpt::A , intr , intrpt::Falling_edge);
	NVIC_EnableIRQ(EXTI0_1_IRQn);
	

	while (1)
	{
		
	}
}
