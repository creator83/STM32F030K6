#include "stm32f0xx.h"                  // Device header
#include "delay.h"

void init_gpio (void);

int main ()
{
	init_gpio ();
	while (1)
	{
		GPIOA->ODR ^= GPIO_ODR_7;
		delay_ms (1000);
	}
}

void init_gpio (void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER7;
	GPIOA->MODER |= GPIO_MODER_MODER7_0;
}
