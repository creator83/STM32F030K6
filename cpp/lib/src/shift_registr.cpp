#include "shift_registr.h"

PtrSend Shift::commandSend [2] = { &Shift::send_hardware, &Shift::send_software};


Shift::Shift(Spi &s, Gpio::Port p, uint8_t pin_)
:cs (p, pin_, Gpio::PushPull)
{
	mod = &s;
	m = mod->GetSpiMode();
	setMode();
	cs.set ();
}

void Shift::setMode ()
{
	SPI1->CR1 &= ~ SPI_CR1_SPE;
	//===settings GPIO===//
	//CS
	
	//settings SPI
	mod->setCpha(Spi::first);
	mod->setCpol(Spi::neg);
	mod->setBaudrate(Spi::div8);
	mod->setFsize(Spi::bit_8);
	SPI1->CR1 |= SPI_CR1_SPE;
}

void Shift::send (uint8_t data)
{
	(this->*(Shift::commandSend[m]))(data);
}

void Shift::send_hardware (uint8_t data)
{
	while (!mod->flagTxe());
	mod->putData(data);
	while (mod->flagBsy());
}

void Shift::send_software (uint8_t data)
{
	cs.clear();
	while (!mod->flagTxe());
	mod->putData(data);
	while (mod->flagBsy());	
	cs.set();
}


