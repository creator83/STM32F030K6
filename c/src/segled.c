#include "segled.h"

//led digit
char number [13] = {0x7B , 0x0A , 0xB3 , 0x9F , 0xCA , 0xD9 , 0xF9 , 0x0B , 0xFB , 0xDB , 0x00, 0x60, 0x6A};
//heater mode
//char mode [3] = {0, 0x60, 0x6A};

char buff [4];

char pins[4] = {DIGIT1, DIGIT2, DIGIT3, DIGIT4};
char flag = 0;

extern uint8_t button_enc;

uint8_t n;


void TIM17_IRQHandler(void)
{
	static uint8_t i=0;
	TIM17->SR &= ~TIM_SR_UIF;
	if (flag) flag=0;
	else
	{
		Show_digit (i);
		flag = 1;
		++i;
	}
	if (i>=n)i=0;
}

void segled_init (void)
{
	//===Settings pins===//
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN|RCC_AHBENR_GPIOBEN;/*
	PORT->MODER |= ((1<< (DIGIT1<<1))|(1<< (DIGIT2<<1))|(1<< (DIGIT3<<2))|(1<< (DIGIT4<<1)));
	PORT->OTYPER &= ~(1<<DIGIT1|1<<DIGIT2|1<<DIGIT3|1<<DIGIT4);
	PORT->OSPEEDR |= ((3<< (DIGIT1<<2))|(3<< (DIGIT2<<2))|(3<< (DIGIT3<<2))|(3<< (DIGIT4<<2)));*/
	GPIOA->MODER &= ~(GPIO_MODER_MODER0|GPIO_MODER_MODER1|GPIO_MODER_MODER2|GPIO_MODER_MODER3);
	GPIOA->MODER |= GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER2_0|GPIO_MODER_MODER3_0;
	GPIOB->MODER &=~(GPIO_MODER_MODER0|GPIO_MODER_MODER1|GPIO_MODER_MODER3|GPIO_MODER_MODER4|GPIO_MODER_MODER5|GPIO_MODER_MODER6|GPIO_MODER_MODER7);
	GPIOB->MODER |= (GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER3_0|GPIO_MODER_MODER4_0|GPIO_MODER_MODER5_0|GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0);
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_0|GPIO_OTYPER_OT_1|GPIO_OTYPER_OT_3|GPIO_OTYPER_OT_4|GPIO_OTYPER_OT_5|GPIO_OTYPER_OT_6|GPIO_OTYPER_OT_7);
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR0|GPIO_OSPEEDR_OSPEEDR1|GPIO_OSPEEDR_OSPEEDR3|GPIO_OSPEEDR_OSPEEDR4|GPIO_OSPEEDR_OSPEEDR5|GPIO_OSPEEDR_OSPEEDR6|GPIO_OSPEEDR_OSPEEDR7;
	
	//===Settings timer===//
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
	TIM17->PSC = 48 - 1;
	TIM17->ARR = 2000;
	TIM17->DIER |= TIM_DIER_UIE;
	TIM17->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ (TIM17_IRQn);
}

void Show_digit (uint8_t dig)
{
	PORT->ODR &= ~(1<<DIGIT1|1<<DIGIT2|1<<DIGIT3|1<<DIGIT4);
	GPIOB->ODR = 0;
	PORT->ODR |= 1 << pins[dig];
	GPIOB->ODR = number [buff [dig]];
}

#ifdef PPR_SOLDER
void buffer (uint16_t val)
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

void buffer (uint16_t val)
{
	char tous, hundr, dec, ones;
	uint16_t temp = val;
	//tous = val/1000;
	for (tous=0;temp>=1000;++tous)temp -=1000;

	for (hundr=0;temp>=100;++hundr)temp -=100;
	
	for (dec=0;temp>=10;++dec)temp -=10;

	for (ones=0;temp>=1;++ones)temp--;
	
	//hundr = (val - tous*1000)/100;
	//dec = (val - (tous*1000 + hundr*100))/10;
	//ones = val%10;
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
	else
	{
		buff[2] = hundr;
		buff[1] = dec;
		buff[0] = ones;
		n=3;
	}
}
#endif

/*
void buffer (uint16_t val)
{
	char tous, hundr, dec, ones, temp;
	tous = division (val);
	temp = division (tous);
	tous = division (temp);
	temp = division (val - (tous*1000));
	hundr = division (temp);
	temp =   division (val - ((tous*1000)+(hundr*100)));
	dec = division (temp);
	//ones = (uint8_t)val%10;
	
	{
		n = 4;
		buff[3] = ones;
		buff[2] = dec;
		buff[1] = hundr;
		buff[0] =tous;
	}
	else
	{
		
		if (hundr)
		{
			n=3;
			buff[2] = dec;
			buff[1] = hundr;
			buff[0] =tous;
		}
		else
		{
			if (dec)
			{
				n=2;
				buff[1] = hundr;
				buff[0] =tous;
			}
			else
			{
				n=1;
				buff[0] =tous;
			}
		}
	}

}*/


uint16_t division (uint16_t n)
{
	uint32_t quot, qq;
	uint8_t rem;
// Multiplay 0.8	
	quot = n >> 1;
  quot += quot >> 1;
  quot += quot >> 4;
  quot += quot >> 8;
  quot += quot >> 16;
  qq = quot;
// devision 8
  quot >>= 3;
//calculate rem
  rem = (uint8_t)(n - ((quot << 1) + (qq & ~7ul)));
// correct
    if(rem > 9)
    {
        rem -= 10;
        quot++;
    }
    return quot;

}
