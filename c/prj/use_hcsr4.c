#include "stm32f0xx.h"                  // Device header
#include "uart.h"
#include "hcsr4.h"
#include "tact.h"


#define  Start   1
#define  Stop   0

extern uint32_t N_takt;
extern char buff [4];
extern char n;
uint8_t flag ;

void EXTI0_1_IRQHandler(void)
{
  uint8_t i;
	EXTI->PR |= 1 << echo;
	if (GPIOA->IDR & (1 << echo))
	{	
		timer_Start_Stop (Start);
		flag=0;
	}
	else
	{/*
		timer_Start_Stop (Stop);
		transmit_byte (HC_SRC4_Convert_CM (N_takt)); 
		flag=1;*/
		
		timer_Start_Stop (Stop);
    HC_SRC4_to_buff (HC_SRC4_Convert_CM (N_takt));
		transmit_string ("==");
    for (i=0;i<4;++i)
    {
			transmit_byte (buff[i]);
    }
    transmit_string ("cm==");           //transmit_byte (HC_SRC4_Convert_CM (N_takt)); 
		flag=1;
	}
}



void init_led (void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER0_0;

}
int main ()
{
	init_HSI ();
	init_PLL ();
	//init_led();
	
		uart_init ();
		HC_SRC4_Init();
	
	while (1)
	{
		//GPIOA->ODR ^= 1 << 0;
	//	delay_ms (1000);
		if (flag)
		{
			HC_SRC4_Send_strob ();
		}
		delay_ms (500);
		
	}
}
