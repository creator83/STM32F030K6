#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "spi.h"
#include "delay.h"

#define F_CPU 48000000
#define tick 1000
#define systick_ms 1
#define systick_val (F_CPU/tick)*systick_ms

void init_p (void);

char number_1 [13] = {0x3F ,0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D, 0x07 , 0x7F , 0x6F ,  0x00, 0x60, 0x6A};
int main ()
{
	uint8_t i;
	//SysTick_Config (systick_val);
	init_p ();
	init_spi_8 ();
	
	while(1)
	{
		
		for (i=0;i<13;++i)
		{
			CS_CLEAR;
			spi1_tx_8 (number_1 [i]);
			CS_SET;
			delay_ms (1000);			
		}	
	}
}



void init_p (void)
	
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	GPIOA->MODER |= GPIO_MODER_MODER0_0;
	GPIOA->ODR |= 1 << 0;
}


