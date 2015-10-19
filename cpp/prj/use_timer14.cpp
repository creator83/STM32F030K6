#include "stm32f0xx.h"
#include "Gpio.h"
#include "tact.h"
#include "timer14.h"


const uint8_t pin=1;
	Gpio A (Gpio::A);
	tact frq;
	timer14 timer (300, timer14::ms);
	
	extern "C"
{
	void TIM14_IRQHandler(void);
}

void TIM14_IRQHandler(void)
{
	A.ChangePinState (pin);
	timer.ClearFlag();
}

int main ()
{
	
	Gpio A (Gpio::A);
	A.setOutPin (pin);
	
	timer.interrupt (timer14::Update);
	timer.Start();
	

	while (1)
	{
	}
}
