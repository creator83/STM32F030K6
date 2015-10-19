#include "stm32f0xx.h"                  // Device header

#define led 0


int main ()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN ;
	GPIOA->MODER = 0;
	GPIOA->MODER |= GPIO_MODER_MODER0_0 ;
	GPIOA->ODR |= 1 << led;
	while (1)
	{
		
	}
}
