#include "stm32f0xx.h"
#include "gpio.h"
#include "tact.h"
#include "pwm.h"
#include "delay.h"
#include "qenc.h"
#include "gtimer.h"

	extern "C"
{
	void TIM14_IRQHandler(void);
}




int main ()
{
	Gtimer timer14 (Gtimer::Timer14, 100);
	Qenc encoder (1000);
	Pwm led_pwm (timer14, Gpio::B, 1, Gpio::AF0, Gtimer::channel1, Pwm::EdgePwm, Pwm::highPulse);
	led_pwm.start();

	while (1)
	{
		led_pwm.setValue (encoder.getValue());
		delay_ms (1);
		/*for (uint16_t i=0;i<=1000;i+=100)
		{
			led_pwm.setValue (i);
			delay_ms (10);
		}
		for (int16_t i=1000;i>=0;i-=100)
		{
			led_pwm.setValue (i);
			delay_ms (10);
		}		*/
	}
}
