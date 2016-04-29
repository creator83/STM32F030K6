#include "delay.h"

//uint16_t delay;


/*
void TIM16_IRQHandler ()
{
	TIM16->SR &= ~TIM_SR_UIF;
	if (delay > 0)delay--;
}*/


 void delay_ms(uint16_t delay)
 {
	 NVIC_SetPriority(TIM16_IRQn, 1);
   RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
   TIM16->PSC = tact::get_frq()*1000 - 1;
   TIM16->ARR = delay;
   TIM16->EGR |= TIM_EGR_UG;
   TIM16->CR1 |= TIM_CR1_OPM;
   TIM16->CR1 |= TIM_CR1_CEN;
   while (TIM16->CR1&TIM_CR1_CEN);
 }
/*
  void delay_ms(uint16_t del)
 {
	 
   RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
   TIM16->PSC = tact::get_frq()*1000 - 1;
   TIM16->ARR = 1;
   TIM16->DIER |= TIM_DIER_UIE;
	 delay = del;
	 //TIM16->CR1 |= TIM_CR1_OPM;
	 //TIM16->CNT = 0;
	 NVIC_EnableIRQ(TIM16_IRQn);
	 NVIC_SetPriority(TIM16_IRQn, 2);
   TIM16->CR1 |= TIM_CR1_CEN;
	 while (delay);
 }*/
 
void delay_us(uint16_t delay)
 {
   NVIC_SetPriority(TIM16_IRQn, 3);
	 RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
   TIM16->PSC = tact::get_frq() - 1;
   TIM16->ARR = delay;
   TIM16->EGR |= TIM_EGR_UG;
   TIM16->CR1 |= TIM_CR1_OPM;
   TIM16->CR1 |= TIM_CR1_CEN;
   while (TIM16->CR1&TIM_CR1_CEN);   
 }

 
 