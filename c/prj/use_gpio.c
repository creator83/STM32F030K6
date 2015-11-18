#include "stm32f0xx.h"                  // Device header
#include "delay.h"

#define delay 1000

void SysTick_Handler (void)
{
	static uint16_t del=0;
	++del;
	if (del > delay)
	{
		GPIOA->ODR ^= GPIO_ODR_15;
		del = 0;
	}
}


void init_gpio (void);

int main ()
{
	init_gpio ();
	SysTick_Config (48000000/1000);
	while (1)
	{

	}
}

void init_gpio (void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER15;
	GPIOA->MODER |= GPIO_MODER_MODER15_0;
}
