#include "gpio.h"

GPIO_TypeDef* Gpio::GpioBase [6] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF};

Gpio::Gpio (Port p)
{
  prt = p;
//takt port
  RCC->AHBENR |= (0x20000 << p);
}

Gpio::Gpio(uint8_t p )
{
  prt = p;
//takt port
  RCC->AHBENR |= (0x20000 << p);
}


void Gpio::settingPin (uint8_t pin , mode m )
{
	
}

void Gpio::setOutPin (unsigned char pin , mode m , speed s , out o)	
{
	GpioBase [prt]->MODER|= (m << (2*pin));
	GpioBase [prt]->OTYPER |= (o << pin);
	GpioBase [prt]->OSPEEDR |= (s << (2*pin));
}

void Gpio::setInPin (unsigned char pin , PP p)
{
	GpioBase [prt]->MODER &= ~(0x03 << (2*pin));
	GpioBase [prt]->PUPDR |= (p << (2*pin));
}

void Gpio::setPin (unsigned int pin )
{
	GpioBase [prt]->BSRR |= 1 << pin;
}

void Gpio::clearPin (unsigned char pin)
{
	GpioBase [prt]->BSRR|= (1 << (pin+16));
}

void Gpio::ChangePinState (unsigned char pin)
{
	GpioBase [prt]->ODR ^= 1 << pin;
}

void Gpio::SetPinState (unsigned char pin , unsigned char state)
{
  if (state)setPin (pin);
  else clearPin (pin);  
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

bool Gpio::PinState (unsigned char pin)
{
  return ((GpioBase [prt]->IDR)&(1 << pin));
}
