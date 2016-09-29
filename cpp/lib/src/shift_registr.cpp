#include "shift_registr.h"

PtrSend Shift::commandSend [2] = { &Shift::send_hardware, &Shift::send_software};


Shift::Shift(Spi &s)
{
	mod = &s;
	m = mod->GetSpiMode();
	setMode();
}

void Shift::setMode ()
{
	SPI1->CR1 &= ~ SPI_CR1_SPE;
	//===settings GPIO===//
	//CS
	mod->set_CS(ShiftDef::CsPort, ShiftDef::CsPin, Gpio::AF0);

	//SCK
	mod->set_SCK(ShiftDef::SckPort, ShiftDef::SckPin, Gpio::AF0);

	//MOSI
	mod->set_MOSI(ShiftDef::MosiPort, ShiftDef::MosiPin, Gpio::AF0);

	//settings SPI
	mod->set_cpha(Spi::first);
	mod->set_cpol(Spi::neg);
	mod->set_baudrate(Spi::div8);
	mod->set_f_size(Spi::bit_8);
	SPI1->CR1 |= SPI_CR1_SPE;
}

void Shift::send (uint8_t data)
{
	(this->*(Shift::commandSend[m]))(data);
}

void Shift::send_hardware (uint8_t data)
{
	while (!mod->flag_txe());
	mod->put_data(data);
	while (mod->flag_bsy());
}

void Shift::send_software (uint8_t data)
{
	mod->assert_Cs(ShiftDef::CsPin);
	while (!mod->flag_txe());
	mod->put_data(data);
	while (mod->flag_bsy());	
	mod->disassert_Cs (ShiftDef::CsPin);
}


