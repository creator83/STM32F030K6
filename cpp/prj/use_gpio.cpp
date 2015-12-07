#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "systimer.h"


tact frq;
Gpio B (Gpio::B);

const char pin = 0;

extern "C"
{
  void SysTick_Handler ();
}

/*
void init_int ()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    EXTI->IMR |= 1 << pin;
    EXTI->RTSR |= 1 << pin;
    //SYSCFG->EXTICR = 0;
    //NVIC_EnableIRQ (EXTI0_1_IRQn);

    
}
*/

void SysTick_Handler ()
{
	static uint16_t i=0;
	if (i>=1000)
	{
		B.ChangePinState (pin);
		i=0;
	}
	else ++i;
}


int main()
{
	systimer (systimer::ms, 1);
	B.setOutPin (pin);



  while (1)
  {

  }
}
