#include "max6675.h"

Ptrdata Max6675::receiveF [2] = {&Max6675::};

Max6675::Max6675 (Spi &s)
{
	mod = &s;
	m = mod->GetSpiMode();
	setMode();
}



void Max6675::setMode ()
{
//===settings GPIO===//
	//CS
	mod->set_CS(Max6675Def::CsPort, Max6675Def::CsPin, Gpio::AF0);

	//SCK
	mod->set_SCK(Max6675Def::SckPort, Max6675Def::SckPin, Gpio::AF0);

	//MOSI
	mod->set_MISO(Max6675Def::MisoPort, Max6675Def::MisoPin, Gpio::AF0);

	//settings SPI
	mod->set_cpha(Spi::second);
	mod->set_cpol(Spi::neg);
	mod->set_baudrate(Spi::div8);
	mod->set_f_size(Spi::bit_16);
}

bool Max6675::readCelsius()
{
	(this->*(Max6675::commandSend[m]))(data);
}

bool Max6675::readCelsius_hardware()
{
	while (!mod->flag_txe());
	mod->put_data(0);
	while (!mod->flag_rxne());
	temp = mod->get_data();
	  if (temp & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }
	temp>>=5;
}

bool Max6675::readCelsius_software()
{
	mod->assert_Cs(Max6675Def::CsPin);
	//delay_ms (200);
	while (!mod->flag_txe());
	mod->put_data(0);
	while (!mod->flag_rxne());
	temp = mod->get_data();
	mod->disassert_Cs (Max6675Def::CsPin);
	if (temp & 0x4) {
    // uh oh, no thermocouple attached!
  return false; 
    //return -100;
  }
	temp>>=5;
	return true;
}
