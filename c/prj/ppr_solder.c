#include "stm32f0xx.h"                  // Device header
#include "max6675.h"
#include "tact.h"
#include "delay.h"
#include "segled.h"
#include "encoder.h"
#include "menu.h"


uint16_t stock_temp = 260;
uint16_t stock_beeper = 5;

extern uint8_t button_enc, flag1, flag_seg, flag_tim;

extern uint16_t current_temp;




int main ()
{
	max6675_init ();
	encoder_init ();	
	button_enc_init ();
	tim14_init ();
	segled_init ();
	
	
	while (1)
	{
		if (flag_seg)
		{
			stock_temp = TIM1->CNT >> 2;
			buffer (stock_temp);
			
		}
		else buffer (current_temp);
		/*
		buffer (readCelsius());
		delay_ms (500);*/
		
		switch (flag1)
		{
			//Short press button_enc
			case 1:
				GPIOA->ODR ^= 1 << 15;
				button_enc++;
				if (button_enc>2) button_enc = 0;
				flag1=0;	
				break;
			case 2:
				flag_seg ^= 1;	
				flag1=0;
				TIM1->CNT = (stock_temp<<2) + 1;
				break;
			//Short press button
			case 3:
				GPIOA->ODR |= 1 << 15;
				delay_ms (500);
				GPIOA->ODR &= ~(1 << 15);
				delay_ms (500);
				GPIOA->ODR |= 1 << 15;
				delay_ms (500);
				GPIOA->ODR &= ~(1 << 15);
				delay_ms (500);			
				flag1=0;
				break;
			//long press button
			case 4:
				GPIOA->ODR |= 1 << 15;
				delay_ms (1500);
				GPIOA->ODR &= ~(1 << 15);
				delay_ms (1500);
				GPIOA->ODR |= 1 << 15;
				delay_ms (1500);
				GPIOA->ODR &= ~(1 << 15);
				delay_ms (1500);			
				flag1=0;
				break;
		}
			/*
		//Short press button_enc
		if (flag1==1)
		{
			GPIOA->ODR ^= 1 << 15;
			button_enc++;
			if (button_enc>2) button_enc = 0;
			flag1=0;
		}	
		//long press button_enc
		if (flag1==2)
		{
			NVIC_DisableIRQ(TIM14_IRQn);
			flag_seg ^= 1;	
			flag1=0;
			TIM1->CNT = (stock_temp<<2) + 1;
			NVIC_EnableIRQ (TIM14_IRQn);
		}
		
		//Short press button
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
		//long press button
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
		}			*/
	}
	
}
