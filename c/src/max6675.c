#include "max6675.h"
#include "spi.h"

#ifdef SOFTSPI

void max6675_init (void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	PORT_->MODER &= ~(GPIO_MODER_MODER4|GPIO_MODER_MODER6|GPIO_MODER_MODER3);
	PORT_->MODER |=GPIO_MODER_MODER3_0|GPIO_MODER_MODER6_0;
	PORT_->ODR &= ~(1 << sck);
	PORT_->ODR |= (1 << cs);
}


uint16_t spiread (void)
{
	int8_t i;
	uint16_t d=0;
	for (i=15;i>=0;--i)
	{
		PORT_->ODR |= 1 << sck;
		delay_ms (1);
		PORT_->ODR &=~ (1 << sck);
		if ((PORT_->IDR & (1 << miso))) d|= (1 << i);
		
		delay_ms (1);
	}
	return d;
}

uint16_t readCelsius(void)
{
  uint16_t v;

  PORT_->ODR &= ~(1 << cs);
  //delay_ms(1);

  v = spiread();

  PORT_->ODR |= (1 << cs);

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }

  v >>= 5;
	
  return v;
}

#else

void max6675_init (void)
{
	init_spi_16 ();
}

uint16_t readCelsius(void)
{
  uint16_t v;

  CS_CLEAR;
  //delay_ms(1);

  v = spi1_rx_16();

  CS_SET;

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }

  v >>= 5;
	
  return v;
}
#endif

//===Spi8 code===//
/*
void max6675_init (void)
{
	init_spi_8 ();
}

uint16_t readCelsius(void)
{
  uint16_t v;

  CS_CLEAR;
  //delay_ms(1);
  v = spi1_rx_8();
	v <<= 8;
	v |= spi1_rx_8();
  CS_SET;

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }

  v >>= 5;
	
  return v;
}

*/

/*
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
}*/












