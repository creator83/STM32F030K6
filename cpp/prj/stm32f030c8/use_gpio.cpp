#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "systimer.h"

const char pin = 8;

tact frq;
Gpio B (Gpio::B);


int main()
{
	B.setOutPin (pin);



  while (1)
  {
		B.setPin (pin);
		delay_ms (1000);
		B.clearPin (pin);
		delay_ms (1000);		
		
  }
}
