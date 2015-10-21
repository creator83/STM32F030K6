#include "max6675.h"
#include "spi.h"



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
	spi1_init ();
}

uint8_t readCelsius(void)
{
  uint16_t v;

  CS_CLEAR();
  delay_ms(1);

  v = SPI_ReceiveData8 (SPI1);
  v <<= 8;
  v |= SPI_ReceiveData8 (SPI1);

  CS_SET();

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }

  v >>= 3;

  return (uint8_t)v*0.25;
}
#endif






