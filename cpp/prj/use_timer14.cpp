#include "stm32f0xx.h"
#include "gpio.h"
#include "tact.h"
#include "pwm.h"
#include "delay.h"

	extern "C"
{
	void TIM14_IRQHandler(void);
}


int main ()
{
	Pwm led_pwm (Gtimer::Timer3, Gtimer::channel3, Pwm::EdgePwm, Pwm::highPulse, Pwm::off);
	led_pwm.setArr (100);
	led_pwm.setChannelValue (50);
	led_pwm.Start();

	while (1)
	{
		for (uint8_t i=0;i<=100;++i)
		{
			led_pwm.setChannelValue (i);
			delay_ms (100);
		}
	}
}
