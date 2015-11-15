#include "menu.h"

uint8_t button_enc, button, flag1, flag_seg, flag_encoder;
uint16_t current_temp;
//typedef 
struct flag
{
	unsigned tim : 1;
	unsigned blink : 1;
}button_enc_flags;


void button_enc_init (void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODER11|GPIO_MODER_MODER10);
	GPIOA->MODER |= GPIO_MODER_MODER15_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_15;
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

void blinking_menu (void)
{
	
}

void TIM14_IRQHandler(void)
{
	
	static uint16_t i=0,j=0,k=0,t=0;
	TIM14->SR &= ~TIM_SR_UIF;	
	++t;
	if (t>300)
	{
		current_temp = readCelsius();
		t=0;
	}
	
	if (k>500)
	{
		button_enc_flags.tim ^=1;
		if(button_enc_flags.tim)
		{
			//off indicator for blinking
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
	//counter for blinking
	if (flag_seg)++k;
	else TIM17->CR1 |= TIM_CR1_CEN;

	
	//===Encoder===//
	//Short press
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
	
	//===Button===//
	//Short press
		if (i>25&&i<300&&GPIOA->IDR&(1 << 10))
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

