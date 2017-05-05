#include "device.h"
#include "gpio.h"
#include "pin.h"
#include "delay.h"
#include "tact.h"
#include "systimer.h"
#include "segled.h"


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

	Pin p (Gpio::Port::A, 1, Gpio::Omode::PushPull);
	while (1)
	{
		p.togle();
		delay_ms (1000);
	}
}
