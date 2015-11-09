#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "delay.h"
#include "segled.h"
#include "encoder.h"

uint8_t button, flag1, flag_seg, flag_tim;

void TIM14_IRQHandler(void)
{
	
	static uint16_t i=0,j=0,k=0;
	TIM14->SR &= ~TIM_SR_UIF;	
	if (k>500)
	{
		flag_tim ^=1;
		if(flag_tim)
		{
			TIM17->CR1 &= ~TIM_CR1_CEN;
			GPIOA->ODR &= ~0x0F;
			k=0;
		}
		else
		{
			TIM17->CR1 |= TIM_CR1_CEN;
			k=0;
		}
			
	}
	if (flag_seg)++k;
	else TIM17->CR1 |= TIM_CR1_CEN;

	
	//===Button===//
	//Quick press
	if (i>25&&i<300&&GPIOA->IDR&(1 << 11))
	{
			flag1=1;
			i=0;
	}
	
	//long press
	if (i>2000&&(!(GPIOA->IDR&(1 << 11))))
	{
		flag1=2;
		i=0;
	}	
	
		//===Encoder===//
		if (j>15&&GPIOA->IDR&(1 << 10))
	{
			flag1=3;
			j=0;
	}
	
		//long press
	if (i>2000&&(!(GPIOA->IDR&(1 << 10))))
	{
			flag1=4;
			j=0;
	}		
	
		if (!(GPIOA->IDR&(1 << 11)))++i;
		else i=0;
		

		if (!(GPIOA->IDR&(1 << 10)))++j;
		else j=0;


}
void button_init (void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODER11|GPIO_MODER_MODER15|GPIO_MODER_MODER10);
	GPIOA->MODER |= GPIO_MODER_MODER15_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_15;
	//GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR10;	
	//GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0;
}

void tim14_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	TIM14->PSC = 48 - 1;
	TIM14->ARR = 1000;
	TIM14->DIER |= TIM_DIER_UIE;
	TIM14->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ (TIM14_IRQn);
}

int main ()
{
	init_HSI ();
	init_PLL ();
	//encoder_init ();
	segled_init ();
	button_init ();
	tim14_init ();
	buffer (5632);
	
	while (1)
	{
		
		if (flag1==1)
		{
			GPIOA->ODR ^= 1 << 15;
			flag1=0;
		}	
		if (flag1==2)
		{
			NVIC_DisableIRQ(TIM14_IRQn);
			flag_seg ^= 1;	
			flag1=0;
			NVIC_EnableIRQ (TIM14_IRQn);
		}
			if (flag1==3)
		{
			NVIC_DisableIRQ(TIM14_IRQn);
			GPIOA->ODR |= 1 << 15;
			delay_ms (500);
			GPIOA->ODR &= ~(1 << 15);
			delay_ms (500);
			GPIOA->ODR |= 1 << 15;
			delay_ms (500);
			GPIOA->ODR &= ~(1 << 15);
			delay_ms (500);			
			flag1=0;
			NVIC_EnableIRQ (TIM14_IRQn);
		}	
			if (flag1==4)
		{
			NVIC_DisableIRQ(TIM14_IRQn);
			GPIOA->ODR |= 1 << 15;
			delay_ms (1500);
			GPIOA->ODR &= ~(1 << 15);
			delay_ms (1500);
			GPIOA->ODR |= 1 << 15;
			delay_ms (1500);
			GPIOA->ODR &= ~(1 << 15);
			delay_ms (1500);			
			flag1=0;
			NVIC_EnableIRQ (TIM14_IRQn);
		}			
	}
}
