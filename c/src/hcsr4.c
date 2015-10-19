#include "hcsr4.h"



uint32_t N_takt;
char number [10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char buff [4];
char n;



void HC_SRC4_Init(void)
{	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	//Trig
	GPIOA->MODER |= GPIO_MODER_MODER1_0;
	
	//Echo
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	init_interp ();
	init_timer ();
}

void HC_SRC4_Send_strob (void)
{
	GPIOA->ODR |= 1 << trig;
	delay_us (20);
	GPIOA->ODR &= ~(1 << trig);
}

void init_interp (void)
{
	EXTI->IMR |= 1 << echo;
	EXTI->FTSR |= 1 << echo;
	EXTI->RTSR |= 1 << echo;
	NVIC_EnableIRQ (EXTI0_1_IRQn);
}

void timer_Start_Stop (char flag)
{
	if (flag)
	{
		TIM14->CNT = 0;
		TIM14->CR1 |= TIM_CR1_CEN;
	}
	else
	{
		TIM14->CR1 &= ~TIM_CR1_CEN;
		N_takt = TIM14->CNT;
	}
}

double HC_SRC4_Convert_CM (uint16_t N_t)
{
	double C = N_t/58.0;
	//C +=1;
	return C;
}

void HC_SRC4_to_buff (double Nmb)
{
	char hundr, dec, ones, decimal;
	/*
  
   hundr = (char)Nmb/100;
   buff [0] = number [hundr];
   if (hundr)
   {
     n=5;
     dec = (char)(Nmb - (hundr*100))/10;
     buff [1] =number [dec];
   }
   else
   {
     n=4;
     dec = (char)Nmb/10;
     buff [1] = number [dec];
   }*/
	 dec = (char)Nmb/10;
	 buff [0] = number [dec];
   ones = ((uint16_t)Nmb)%10;
   buff [1] = number [ones];
   buff [2] = '.';
   decimal = ((char)(Nmb*10.0))%10;
   buff [3] = number [decimal];
}

void init_timer (void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	TIM14->PSC = F_CPU/1000000 - 1;
}


