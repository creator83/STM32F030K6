#include "encoder.h"

void encoder_init (void)
{
	//Turn on tact
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//===Settings pins===//
	GPIOA->MODER &= ~(GPIO_MODER_MODER8|GPIO_MODER_MODER9);
	GPIOA->MODER |= GPIO_MODER_MODER8_1|GPIO_MODER_MODER9_1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR8_0|GPIO_PUPDR_PUPDR9_0;
	GPIOA->AFR[1] = (2 << 0)|(2 << 4);
	
	//===Settings timer===//
	TIM1->CCMR1 |= TIM_CCMR1_IC1F|TIM_CCMR1_IC2F;
	TIM1->CCMR1 |= TIM_CCMR1_CC1S_0|TIM_CCMR1_CC2S_0;
	TIM1->CCER &=  ~(TIM_CCER_CC1P|TIM_CCER_CC2P);
	TIM1->SMCR |= TIM_SMCR_SMS_0|TIM_SMCR_SMS_1;
	TIM1->CR1 |= TIM_CR1_CEN;
	TIM1->CNT = 0;
}
