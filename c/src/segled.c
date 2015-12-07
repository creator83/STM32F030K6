#include "segled.h"

//led digit
#ifdef PORTA
char number [13] = {0x3F ,0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D, 0x07 , 0x7F , 0x6F ,  0x00, 0x60, 0x6A};
#else
char number [13] = {0x7B , 0x0A , 0xB3 , 0x9F , 0xCA , 0xD9 , 0xF9 , 0x0B , 0xFB , 0xDB , 0x00, 0x60, 0x6A};
#endif
/*//heater mode
//char mode [3] = {0, 0x60, 0x6A};
*/
char buff [4];

char pins[4] = {DIGIT1, DIGIT2, DIGIT3, DIGIT4};

extern uint8_t button_enc;

uint8_t n;



void segled_init (void)
{
	//===Settings pins===//
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN|RCC_AHBENR_GPIOBEN;/*
	PORT->MODER |= ((1<< (DIGIT1<<1))|(1<< (DIGIT2<<1))|(1<< (DIGIT3<<2))|(1<< (DIGIT4<<1)));
	PORT->OTYPER &= ~(1<<DIGIT1|1<<DIGIT2|1<<DIGIT3|1<<DIGIT4);
	PORT->OSPEEDR |= ((3<< (DIGIT1<<2))|(3<< (DIGIT2<<2))|(3<< (DIGIT3<<2))|(3<< (DIGIT4<<2)));*/
#ifdef PORTA
	//Settings Digit//
	GPIOA->MODER &= ~(GPIO_MODER_MODER10|GPIO_MODER_MODER11|GPIO_MODER_MODER12|GPIO_MODER_MODER15);
	GPIOA->MODER |= GPIO_MODER_MODER10_0|GPIO_MODER_MODER11_0|GPIO_MODER_MODER12_0|GPIO_MODER_MODER15_0;
	//Settings segment//
	GPIOA->MODER &=~0x3FFF;
	GPIOA->MODER |= 0x1555;
	GPIOA->MODER |= (GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER3_0|GPIO_MODER_MODER4_0|GPIO_MODER_MODER5_0|GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0);
	GPIOA->OTYPER &= ~0x7F;
	GPIOA->OSPEEDR |= 0x3FFF;;
#else
	GPIOA->MODER &= ~(GPIO_MODER_MODER0|GPIO_MODER_MODER1|GPIO_MODER_MODER2|GPIO_MODER_MODER3);
	GPIOA->MODER |= GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER2_0|GPIO_MODER_MODER3_0;
	GPIOB->MODER &=~(GPIO_MODER_MODER0|GPIO_MODER_MODER1|GPIO_MODER_MODER3|GPIO_MODER_MODER4|GPIO_MODER_MODER5|GPIO_MODER_MODER6|GPIO_MODER_MODER7);
	GPIOB->MODER |= (GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER3_0|GPIO_MODER_MODER4_0|GPIO_MODER_MODER5_0|GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0);
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_0|GPIO_OTYPER_OT_1|GPIO_OTYPER_OT_3|GPIO_OTYPER_OT_4|GPIO_OTYPER_OT_5|GPIO_OTYPER_OT_6|GPIO_OTYPER_OT_7);
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR0|GPIO_OSPEEDR_OSPEEDR1|GPIO_OSPEEDR_OSPEEDR3|GPIO_OSPEEDR_OSPEEDR4|GPIO_OSPEEDR_OSPEEDR5|GPIO_OSPEEDR_OSPEEDR6|GPIO_OSPEEDR_OSPEEDR7;
#endif
	/*
	//===Settings timer===//
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
	TIM17->PSC = 48 - 1;
	TIM17->ARR = 2000;
	TIM17->DIER |= TIM_DIER_UIE;
	TIM17->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ (TIM17_IRQn);*/
}

void Show_digit (uint8_t dig)
{
#ifdef PORTA
	PORT->ODR &= ~(1<<DIGIT1|1<<DIGIT2|1<<DIGIT3|1<<DIGIT4);
	GPIOA->ODR &= ~0x7F;
	PORT->ODR |= 1 << pins[dig];
	GPIOA->ODR |= number [buff [dig]];	
#else
	PORT->ODR &= ~(1<<DIGIT1|1<<DIGIT2|1<<DIGIT3|1<<DIGIT4);
	GPIOB->ODR = 0;
	PORT->ODR |= 1 << pins[dig];
	GPIOB->ODR = number [buff [dig]];
#endif
}

void led_number ()
{
	static uint8_t i=0;
	Show_digit (i);
	++i;
	if (i>=n)i=0;
}

void led_on (void)
{
	
}

void led_off (void)
{
	
}

void led_char (uint8_t ch, uint8_t n)
{
}

#ifdef PPR_SOLDER
void segled_buffer (uint16_t val)
{
	char hundr, dec, ones;
	uint16_t temp = val;
	for (hundr=0;temp>=100;++hundr)temp -=100;
	
	for (dec=0;temp>=10;++dec)temp -=10;

	for (ones=0;temp>=1;++ones)temp--;
	n=4;
		if (hundr)
	{	
		buff[3] = button_enc+OFF;
		buff[2] = hundr;
		buff[1] = dec;
		buff[0] = ones;
	}
		else if (!(dec || hundr))
	{
		buff[3] = button_enc+OFF;
		buff[2] = OFF;
		buff[1] = OFF;
		buff[0] = ones;
	}
	else
	{
		buff[3] = button_enc+OFF;
		buff[2] = OFF;
		buff[1] = dec;
		buff[0] = ones;
	}
}
#else

void segled_buffer (uint16_t val)
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
#endif
