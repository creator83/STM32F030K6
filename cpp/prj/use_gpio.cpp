#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"


  tact frq;
	Gpio B (Gpio::B);

//const uint8_t pin = 0;
const uint8_t out = 7;
//Gpio A (Gpio::A);
/*
extern "C"
{
  void EXTI0_1_IRQHandler();
}



void EXTI0_1_IRQHandler()
{
  EXTI->PR |= 1 << pin;
  A.ChangePinState (out);			
}

void init_int ()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    EXTI->IMR |= 1 << pin;
    EXTI->RTSR |= 1 << pin;
    //SYSCFG->EXTICR = 0;
    //NVIC_EnableIRQ (EXTI0_1_IRQn);

    
}
*/

int main()
{
	//init_int ();
	B.setOutPin (out);



  while (1)
  {
   B.ChangePinState (out);
		delay_ms (1000);
  }
}
