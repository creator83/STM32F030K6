#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "Spi.h"
 
  Gpio A (Gpio::A);
  const char pin = 0;
  spi spi1 (spi::div4);
  
  extern "C"
  {
    void EXTI0_1_IRQHandler();
  }
void EXTI0_1_IRQHandler(void)
{
    EXTI->PR |= 1 << pin;
	      for (uint8_t i = 0 ;i<8;++i)
    {
      spi1.Clear_CS();
      spi1.transfer (1 << i);
      spi1.Set_CS();
      delay_ms (50);
    }
     for (uint8_t i = 6 ;i>0;--i)
    {
      spi1.Clear_CS();
      spi1.transfer (1 << i);
      spi1.Set_CS();
      delay_ms (200);
    }

}
void init_int ()
{
    A.setInPin (pin);
    EXTI->IMR |= 1 << pin;
    EXTI->RTSR |= 1 << pin;
    NVIC_EnableIRQ (EXTI0_1_IRQn);
}


int main()
{
	tact frq;
	init_int ();


  
  while (1)
  {

  }
}
