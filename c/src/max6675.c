#include "max6675.h"
#include "spi.h"

char max6675_number [10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char max6675_buff [4] = {0, 0, '.', '0'};


#ifdef SOFTSPI

void max6675_init (void)
{
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  GPIOA->MODER &= ~(GPIO_MODER_MODER4|GPIO_MODER_MODER5|GPIO_MODER_MODER6);
  GPIOA->MODER |= GPIO_MODER_MODER5_0|GPIO_MODER_MODER4_0;
}

uint8_t spiread(void)
{
  int8_t i;
  uint8_t d = 0;

  for (i=7; i>=0; i--)
  {
    GPIOA->ODR &=~(1 << sclk);
    delay_ms(1);
    if ((GPIOA->IDR & (1 << miso)))
    {
      //set the bit to 0 no matter what
      d |= (1 << i);
    }

    GPIOA->ODR |=(1 << sclk);
    delay_ms(1);
  }
  return d;
}

uint8_t readCelsius(void)
{
  uint16_t v;

  GPIOA->ODR &=~(1 << cs);
  delay_ms(1);

  v = spiread();
  v <<= 8;
  v |= spiread();

  GPIOA->ODR |=(1 << cs);

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }

  v >>= 3;

  return (uint8_t)v*0.25-7;
}
#else

void max6675_init (void)
{
	init_spi_16 ();
}
#ifdef Decimal
double readCelsius(void)
{
  uint16_t v;

  clear_cs ();
  delay_ms(1);

  v = spi1_rx_16();

  set_cs ();

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }

  v >>= 3;
	//v >>= 2;
  return v*0.25;
}

void max6675_buffer (double val)
{
	char dec, ones, decimal;
	dec = val/10;
	max6675_buff[0] = max6675_number [dec];
	ones = (int)val%10;
	max6675_buff[1] = max6675_number [ones];
	max6675_buff [2] = '.';
	decimal = (int)(val*10)%10;
	max6675_buff[3] = max6675_number [decimal];
}
#else

uint16_t readCelsius(void)
{
  uint16_t v;

  clear_cs ();
  delay_ms(1);

  v = spi1_rx_16();

  set_cs ();

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }

  v >>= 5;
	
  return v;
}
/*
void max6675_buffer (uint16_t val)
{
	char dec, ones;
	dec = division (val);
	max6675_buff[0] = max6675_number [dec];
	ones = val%10;
	max6675_buff[1] = max6675_number [ones];
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

}*/

#endif

#endif






