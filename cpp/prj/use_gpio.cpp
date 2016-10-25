#include "stm32f0xx.h"
#include "gpio.h"
#include "delay.h"
#include "tact.h"
#include "systimer.h"


Tact frq;


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
}


int main()
{
	Gpio B (Gpio::B);
	B.settingPin (pin);



  while (1)
  {
		B.ChangePinState (pin);
		delay_ms (1000);
  }
}
