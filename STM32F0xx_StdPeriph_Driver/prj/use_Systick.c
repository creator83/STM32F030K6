#include "stm32f0xx.h"                  // Device header

uint16_t delay;

void SysTick_Handler (void)
{
	if (delay > 0)delay--;
}

void delay_ms (uint16_t del)
{
	delay = del;
	while (delay);
}

int main ()
{
	GPIO_InitTypeDef PortA_Led;
	SysTick_Config (SystemCoreClock/1000);
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA, ENABLE);
	PortA_Led.GPIO_Pin = GPIO_Pin_7;
	PortA_Led.GPIO_Mode = GPIO_Mode_OUT;
	PortA_Led.GPIO_Speed = GPIO_Speed_Level_2;
	PortA_Led.GPIO_OType = GPIO_OType_PP;
	GPIO_Init (GPIOA, &PortA_Led);
	while (1)
	{
		GPIO_SetBits (GPIOA, GPIO_Pin_7);
		delay_ms (500);
		GPIO_ResetBits (GPIOA, GPIO_Pin_7);
		delay_ms (500);
	}
}
