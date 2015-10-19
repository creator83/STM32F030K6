#include "delay.h"


 void delay_ms(uint16_t delay)
 {
   RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
   //TIM16->PSC = F_CPU/1000 - 1;
   TIM16->PSC = tact::get_frq()*1000 - 1;
   TIM16->ARR = delay;
   TIM16->EGR |= TIM_EGR_UG;
   TIM16->CR1 |= TIM_CR1_OPM;
   TIM16->CR1 |= TIM_CR1_CEN;
   while (TIM16->CR1&TIM_CR1_CEN);
 }
 
void delay_us(uint16_t delay)
 {
   RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
   TIM16->PSC = tact::get_frq() - 1;
   TIM16->ARR = delay;
   TIM16->EGR |= TIM_EGR_UG;
   TIM16->CR1 |= TIM_CR1_OPM;
   TIM16->CR1 |= TIM_CR1_CEN;
   while (TIM16->CR1&TIM_CR1_CEN);   
 }

 