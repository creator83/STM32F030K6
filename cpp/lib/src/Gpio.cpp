#include "Gpio.h"

unsigned int Gpio::portAdr [6] = {GPIOA_BASE, GPIOB_BASE, GPIOC_BASE,0,0,GPIOF_BASE};
unsigned int Gpio::portAdrBit [6] = {0x42000000, 0x42000400, 0x42000800,0,0,0x42001400};

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

void Gpio::setOutPin (unsigned char pin , mode m , speed s , out o)	
{
  *(reg)(portAdr[prt]+Moder) |= (m << (2*pin));
  *(reg)(portAdr[prt]+Otyper) |= (o << pin);
  *(reg)(portAdr[prt]+Ospeedr) |= (s << (2*pin));
}

void Gpio::setInPin (unsigned char pin , PP p)
{
  *(reg)(portAdr[prt]+Moder) &= ~(0x03 << (2*pin));
  *(reg)(portAdr[prt]+Pupdr) |= (p << (2*pin));
}

void Gpio::setPin (unsigned int pin )
{
  *(reg)(portAdr[prt]+Bsrr) |= 1 << pin;
}

void Gpio::setPinBit (unsigned int pin )
{
  *(reg)(portAdrBit[prt] + 0x1C) = pin ;
}

void Gpio::clearPin (unsigned char pin)
{
  *(reg)(portAdr[prt]+Bsrr) |= (1 << (pin+16));
}

void Gpio::ChangePinState (unsigned char pin)
{
  *(reg)(portAdr[prt]+Odr) ^= 1 << pin;
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
      *(reg)(portAdr[prt]+Moder) |= (1 << (2*i));
      *(reg)(portAdr[prt]+Ospeedr) |= (1 << (2*i));
    }
    *(reg)(portAdr[prt]+Otyper) &= ~(value);
  }
}

void Gpio::setValPort (unsigned int value)
{
  *(reg)(portAdr[prt]+Bsrr) |= value;
}

void Gpio::clearPort (unsigned int value)
{
	*(reg)(portAdr[prt]+Bsrr) |= (value << 16);
}

void Gpio::PuPd (unsigned char pin , PP p)
{
  *(reg)(portAdr[prt]+Pupdr) &= ~(0x03 << (2*pin));
  *(reg)(portAdr[prt]+Pupdr) |= (p << (2*pin));
}

bool Gpio::PinState (unsigned char pin)
{
  return ((*(reg)(portAdr[prt]+Idr))&(1 << pin));
}
