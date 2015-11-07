#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "delay.h"
#include "segled.h"
#include "encoder.h"

extern char number [11];

int main ()
{
//	uint8_t i, j;
	//uint8_t i;
	
	init_HSI ();
	init_PLL ();
	encoder_init ();
	segled_init ();
	TIM1->CNT = 1044;
	while(1)
	{
		buffer (TIM1->CNT>>2);
		/*i = TIM1->CNT>>2;
		GPIOB->ODR = number [i];
		
		for (j=0;j<4;++j)
		{
			GPIOA->ODR = 1 <<j;
			for (i=0;i<11;++i)
			{
				GPIOB->ODR = number [i];
				delay_ms (200);
			}
		}*/
	}

}
