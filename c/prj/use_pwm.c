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
	//TIM3->PSC |= 4800-1;
	//TIM3->ARR |= 1000;
	TIM3->CCER |= TIM_CCER_CC3E;
	TIM3->CCMR2 |= TIM_CCMR2_OC3M_1|TIM_CCMR2_OC3M_2;
	TIM3->CR1 |= TIM_CR1_CEN;
}

int main ()
{
	uint16_t i;
	init_gpio();
	init_timer ();
	while (1)
	{
		for (i=0;i<0xFFFF;++i)
		{
			TIM3->CCR3 = i;
			delay_us (10);
		}
		for (i=0xFFFF;i>0;--i)
		{
			TIM3->CCR3 = i;
			delay_us (10);
		}		
	}	
}
