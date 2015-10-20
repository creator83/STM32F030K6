#include "stm32f0xx.h"                  // Device header
#define led 7

int main ()
{
	uint32_t i;
	GPIO_InitTypeDef PortA_Led;
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA, ENABLE);
	PortA_Led.GPIO_Pin = GPIO_Pin_7;
	PortA_Led.GPIO_Mode = GPIO_Mode_OUT;
	PortA_Led.GPIO_Speed = GPIO_Speed_Level_2;
	PortA_Led.GPIO_OType = GPIO_OType_PP;
	GPIO_Init (GPIOA, &PortA_Led);
	
	while (1)
	{
		GPIO_SetBits (GPIOA, GPIO_Pin_7);
		for (i=0;i<2000000;++i){}
		GPIO_ResetBits (GPIOA, GPIO_Pin_7);
		for (i=0;i<2000000;++i){}
	}
}
