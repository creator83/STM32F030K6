#include "gpio.h"

GPIO_TypeDef* Gpio::GpioBase [6] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF};

Gpio::Gpio (Port p)
{
  prt = (uint8_t) p;
//takt port
  RCC->AHBENR |= (0x20000 << prt);
}

Gpio::Gpio(uint8_t p )
{
  prt = p;
//takt port
  RCC->AHBENR |= (0x20000 << p);
}

void Gpio::setOutPort (unsigned int value, speed s )
{
  for (uint8_t i = 0;i<16;++i)
  {
    if (value & (1<<i))
    {
			GpioBase [prt]->MODER |= (1 << (2*i));
			GpioBase [prt]->OSPEEDR |= (1 << (2*i));
    }
		GpioBase [prt]->OTYPER &= ~(value);
  }
}

void Gpio::setValPort (unsigned int value)
{
	GpioBase [prt]->BSRR |= value;
}

void Gpio::clearPort (unsigned int value)
{
	GpioBase [prt]->BSRR |= (value << 16);
}

void Gpio::PuPd (unsigned char pin , PP p)
{
	GpioBase [prt]->PUPDR &= ~(0x03 << (2*pin));
	GpioBase [prt]->PUPDR |= (p << (2*pin));
}

