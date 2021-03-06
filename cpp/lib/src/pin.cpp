#include "pin.h"

Pin::Pin(Gpio::Port port, uint8_t p)
:Gpio(port)
{
  pin_=p;
	GpioBase [prt]->MODER &= ~ (0x03 << (2*pin_));
	GpioBase [prt]->MODER|= (static_cast <uint8_t> (Gpio::Mode::Output) << (2*pin_));
	GpioBase [prt]->OTYPER &= ~(1 << pin_);
}

Pin::Pin(Port p_, uint8_t p, Mode m)
:Gpio(p_)
{
  pin_=p;
	GpioBase [prt]->MODER &= ~ (0x03 << (2*pin_));
	GpioBase [prt]->MODER|= (static_cast <uint8_t> (m) << (2*pin_));
}

Pin::Pin(Port port_, uint8_t p, Afmode af)
:Gpio(port_)
{
  pin_=p;
	GpioBase [prt]->MODER &= ~ (0x03 << (2*pin_));
	GpioBase [prt]->MODER|= (0x02 << (2*pin_));
	if (pin_ <7)GpioBase [prt]->AFR[0]|= static_cast <uint8_t> (af) << (4*pin_); 
	else GpioBase [prt]->AFR[1]|= static_cast <uint8_t> (af) << (4*(pin_-8));
}

Pin::Pin(Port port_, uint8_t p, Omode o)
:Gpio(port_)
{
  pin_=p;
	GpioBase [prt]->MODER &= ~ (0x03 << (2*pin_));
	GpioBase [prt]->MODER|= (static_cast <uint8_t> (Gpio::Mode::Output) << (2*pin_));
	GpioBase [prt]->OTYPER &= ~(1 << pin_);
	GpioBase [prt]->OTYPER |= static_cast <uint8_t> (o) << pin_;
}

Pin::Pin(Port port_, uint8_t p, PP p_)
:Gpio(port_)
{
  pin_=p;
	GpioBase [prt]->MODER &= ~ (0x03 << (2*pin_));
	GpioBase [prt]->PUPDR &= ~(0x03 << pin_*2);
	GpioBase [prt]->PUPDR |= static_cast <uint8_t> (p) << pin_*2;
}

void Pin::setInputMode (PP p)
{
	GpioBase [prt]->MODER &= ~ (0x03 << (2*pin_));
	GpioBase [prt]->PUPDR &= ~(0x03 << pin_*2);
	GpioBase [prt]->PUPDR |= static_cast <uint8_t> (p) << pin_*2;
}
	
void Pin::setOutputMode (Omode o)
{
	GpioBase [prt]->MODER &= ~ (0x03 << (2*pin_));
	GpioBase [prt]->MODER|= (0x01 << (2*pin_));
	GpioBase [prt]->OTYPER &= ~(1 << pin_);
	GpioBase [prt]->OTYPER |= static_cast <uint8_t> (o) << pin_;
}


void Pin::set ()
{
	GpioBase [prt]->BSRR |= 1 << pin_;
}

void Pin::clear ()
{
	GpioBase [prt]->BSRR|= (1 << (pin_+16));
}

void Pin::togle ()
{
	GpioBase [prt]->ODR ^= 1 << pin_;
}

bool Pin::state ()
{
	return ((GpioBase [prt]->IDR)&(1 << pin_));
}

GPIO_TypeDef * Pin::getPort ()
{
	return GpioBase[prt];
}

uint8_t & Pin::getPin ()
{
	return pin_;
}
