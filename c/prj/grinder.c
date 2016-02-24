#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "delay.h"
#include "spi.h"

#define F_CPU 48000000
#define tick 1000
#define systick_ms 1
#define systick_val (F_CPU/tick)*systick_ms
void init_p (void);
void Show_digit (uint8_t dig);
void transmite (uint8_t data);
void led_number (void);
void buffer (uint16_t val);

//Цифры
char number [13] = {0x3F ,0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D, 0x07 , 0x7F , 0x6F ,  0x00, 0x60, 0x6A};

//Пины разрядов
char pins[3] = {2,1,0};

//Буффер 
char buff [4];

uint8_t n;

struct flags
{
	unsigned led_indicator_delay : 1;
	unsigned led_indicator : 4;
}flag;

void SysTick_Handler (void)
{
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
			static uint8_t i=0;
	Show_digit (i);
	++i;
	if (i>=n)i=0;
		if (flag.led_indicator>10)
		{
			flag.led_indicator_delay = 1;
			flag.led_indicator = 0;
		}
		flag.led_indicator++;
		
	}
}




int main ()
{
	SysTick_Config (systick_val);
	init_p ();
	init_spi_8 ();
	buffer (236);
	
	while(1)
	{
		
	}
}



void init_p (void)
	
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODER0|GPIO_MODER_MODER1|GPIO_MODER_MODER2);
	GPIOA->MODER |= GPIO_MODER_MODER0_0| GPIO_MODER_MODER1_0| GPIO_MODER_MODER2_0;
	//GPIOA->ODR |= 1 << 0;
}

void Show_digit (uint8_t dig)
{
	GPIOA->ODR &= ~(1<<0|1<<1|1<<2);
	transmite (0);
	GPIOA->ODR |= 1 << pins[dig];
	transmite (number [buff [dig]]);	
}

void transmite (uint8_t data)
{
	CS_CLEAR;
	spi1_tx_8 (data);
	CS_SET;
}

void buffer (uint16_t val)
{
	char tous, hundr, dec, ones;
	uint16_t temp = val;

	for (tous=0;temp>=1000;++tous)temp -=1000;

	for (hundr=0;temp>=100;++hundr)temp -=100;
	
	for (dec=0;temp>=10;++dec)temp -=10;

	for (ones=0;temp>=1;++ones)temp--;

	if (tous)
	{	
		buff[3] = tous;
		buff[2] = hundr;
		buff[1] = dec;
		buff[0] = ones;
		n=4;
	}
	else if (!(tous || hundr))
	{
		buff[1] = dec;
		buff[0] = ones;
		n=2;
	}
	else if (!(tous || hundr||dec))
	{
		buff[0] = ones;
		n=1;
	}	
	else
	{
		buff[2] = hundr;
		buff[1] = dec;
		buff[0] = ones;
		n=3;
	}
}

void led_number (void)
{
	static uint8_t i=0;
	Show_digit (i);
	++i;
	if (i>=n)i=0;
}
