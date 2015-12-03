#include "stm32f0xx.h"  
#include "tact.h"
#include "delay.h"

void init_gpio (void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER &= ~GPIO_MODER_MODER0;
	GPIOB->MODER |= GPIO_MODER_MODER0_1;
	GPIOB->AFR[0] |= 1 <<0; 
}

void init_timer (void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC |= 480-1;
	TIM3->ARR |= 10;
	TIM3->CCER |= TIM_CCER_CC3E;
	TIM3->CCMR2 |= TIM_CCMR2_OC3M_1|TIM_CCMR2_OC3M_2;
	TIM3->CR1 |= TIM_CR1_CEN;
}

int main ()
{
	//uint16_t p []={0,30000,0xFFFF};
	//uint16_t i;
	init_gpio();
	init_timer ();
	TIM3->CCR3 = 58980;
	while (1)
	{
		/*
		for (i=0;i<3;++i)
		{
			TIM3->CCR3 = p[i];
			delay_ms (3000);
		}*/
		
	}	
}
