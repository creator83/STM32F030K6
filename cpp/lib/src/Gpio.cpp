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


void Gpio::settingPin (uint8_t pin , Mode  m )
{
	GpioBase [prt]->MODER &= ~ (0x03 << (2*pin));
	GpioBase [prt]->MODER|= (m << (2*pin));
}

void Gpio::settingPinPort (Port p)
{
	prt = p;
	//takt port
  RCC->AHBENR |= (0x20000 << p);
}

void Gpio::settingAf (uint8_t pin, Afmode a)
{
	if (pin <7)GpioBase [prt]->AFR[0]|= a << (4*pin); 
	else GpioBase [prt]->AFR[1]|= a << (4*(pin-8)); 
}

void Gpio::settingOut (uint8_t pin, Omode o)
{
	GpioBase [prt]->OTYPER &= ~(1 << pin);
	GpioBase [prt]->OTYPER |= o << pin;
}

void Gpio::settingPP (uint8_t pin, PP p)
{
	GpioBase [prt]->PUPDR &= ~(0x03 << pin*2);
	GpioBase [prt]->PUPDR |= p << pin*2;
}

void Gpio::setPin (uint8_t pin )
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

bool Gpio::pinState (unsigned char pin)
{
  return ((GpioBase [prt]->IDR)&(1 << pin));
}
