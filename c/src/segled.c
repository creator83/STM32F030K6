#include "segled.h"

//led digit
char number [11] = {0x7B , 0x0A , 0xB3 , 0x9F , 0xCA , 0xD9 , 0xF9 , 0x0B , 0xFB , 0xDB , 0x00};

char buff [4];

char pins[4] = {};
	
	uint16_t k = 4532;
//
uint8_t n;

void TIM17_IRQHandler(void)
{
	static uint8_t i;
	buffer (k);
	for (i=0;i<n;++i)
	{
		
	}
}

void segled_init (void)
{
	//===Settings pins===//
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN|RCC_AHBENR_GPIOBEN;
	PORT->MODER |= ((1<< (DIGIT1<<2))|(1<< (DIGIT2<<2))|(1<< (DIGIT3<<2))|(1<< (DIGIT4<<2)));
	PORT->OTYPER &= ~(1<<DIGIT1|1<<DIGIT2|1<<DIGIT3|1<<DIGIT4);
	PORT->OSPEEDR |= ((3<< (DIGIT1<<2))|(3<< (DIGIT2<<2))|(3<< (DIGIT3<<2))|(3<< (DIGIT4<<2)));
	GPIOB->MODER |= GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER3_0|GPIO_MODER_MODER4_0|GPIO_MODER_MODER5_0|GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0;
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_0|GPIO_OTYPER_OT_1|GPIO_OTYPER_OT_3|GPIO_OTYPER_OT_4|GPIO_OTYPER_OT_5|GPIO_OTYPER_OT_6|GPIO_OTYPER_OT_7);
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR0|GPIO_OSPEEDR_OSPEEDR1|GPIO_OSPEEDR_OSPEEDR3|GPIO_OSPEEDR_OSPEEDR4|GPIO_OSPEEDR_OSPEEDR5|GPIO_OSPEEDR_OSPEEDR6|GPIO_OSPEEDR_OSPEEDR7;
	
	//===Settings timer===//
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
	TIM17->PSC = 48 - 1;
	TIM17->ARR = 1000;
	TIM17->DIER |= TIM_DIER_UIE;
	TIM17->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ (TIM17_IRQn);
}

void Show_digit (uint8_t number)
{
	
}

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
	ones = val%10;
	if (tous)
	{
		n = 4;
		buff[3] = number [tous];
		buff[2] = number [hundr];
		buff[1] = number [dec];
		buff[0] = number [ones];
	}
	else
	{
		
		if (hundr)
		{
			n=3;
			buff[2] = number [hundr];
			buff[1] = number [dec];
			buff[0] = number [ones];
		}
		else
		{
			if (dec)
			{
				n=2;
				buff[1] = number [dec];
				buff[0] = number [ones];
			}
			else
			{
				n=1;
				buff[0] = number [ones];
			}
		}
	}

}


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
