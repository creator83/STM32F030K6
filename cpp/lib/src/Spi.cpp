#include "spi.h"

SPI_TypeDef * Spi::SpiBase [2] = {SPI1, SPI2};

PotMemFn Spi::ptr_receive[2] = {&Spi::receive_8, &Spi::receive_16};

PotMemF Spi::ptr_transmite[2] = {&Spi::transmit_8, &Spi::transmit_16};
ptr_ex Spi::ptr_exchange[2] =  {&Spi::exchange_8, &Spi::exchange_16};
PtrF1 Spi::spi_mode [2] = {&Spi::hardwareMode, &Spi::softwareMode};

Spi::Spi (Role r, mode m)
:sck (spiDef::sckPort, spiDef::sckPin, spiDef::sckAf),
mosi (spiDef::mosiPort, spiDef::mosiPin, spiDef::mosiAf),
miso (spiDef::misoPort, spiDef::misoPin, spiDef::misoAf)
{
  //tact Spi1
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    
  //Mode Master/Slave
	SPI1->CR1 &= ~ SPI_CR1_MSTR;
	SPI1->CR1 |= r << 2;
    
  //Soft mode 
	spi_m = m;
	(this->*(Spi::spi_mode[m]))();
	
	 //Turn on Spi1
   //
}

Spi::Spi (Role r)
:sck (spiDef::sckPort, spiDef::sckPin, spiDef::sckAf),
mosi (spiDef::mosiPort, spiDef::mosiPin, spiDef::mosiAf),
miso (spiDef::misoPort, spiDef::misoPin, spiDef::misoAf)
{
	 //tact Spi1
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    
  //Mode Master/Slave
	SPI1->CR1 &= ~ SPI_CR1_MSTR;
	SPI1->CR1 |= r << 2;
	spi_m = software;
	softwareMode ();
}

void Spi::hardwareMode ()
{
	SPI1->CR1 &= ~ SPI_CR1_SSM;
	SPI1->CR2 |= SPI_CR2_SSOE;
}

void Spi::softwareMode ()
{
	SPI1->CR1 |= SPI_CR1_SSM;
  SPI1->CR1 |= SPI_CR1_SSI;
}

void Spi::setCpol (Cpol c)
{
	SPI1->CR1 &= ~ SPI_CR1_CPOL;
	SPI1->CR1 |=  c << 1;
}

void Spi::setCpha (Cpha c)
{
	SPI1->CR1 &= ~ SPI_CR1_CPHA ;
	SPI1->CR1 |=  c << 0;	
}

void Spi::setFsize (Fsize f)
{
	SPI1->CR2 &= ~ SPI_CR2_DS;
	SPI1->CR2 |= f << 8;
	if (f <= bit_8) SPI1->CR2 |= SPI_CR2_FRXTH;
}

void Spi::setBaudrate (Division d)
{
	SPI1->CR1 &= ~SPI_CR1_BR;
	SPI1->CR1 |= d << 3;
}


void Spi::start ()
{
	SPI1->CR1 |= SPI_CR1_SPE;
}

void Spi::stop ()
{
	SPI1->CR1 &= ~ SPI_CR1_SPE;
}

void Spi::transmit_8 (uint16_t data)
{
	while (!(SPI1->SR&SPI_SR_TXE));
	*(uint8_t *)&(SPI1->DR) = static_cast <uint8_t> (data);
	while (SPI1->SR&SPI_SR_BSY);
}

void Spi::transmit_16 (uint16_t data)
{
	while (!(SPI1->SR&SPI_SR_TXE));
	SPI1->DR = data;
	while (SPI1->SR&SPI_SR_BSY);
}

void Spi::transmit (uint16_t data)
{
	(this->*(Spi::ptr_transmite[size_]))(data);
}

uint16_t Spi::receive_8 ()
{
	//while (Spi1->SR&Spi_SR_BSY);
	//Spi1_DR_8bit  = 0xFF;
	//Spi1->DR = 0x0000;
	*(uint8_t *)&(SPI1->DR) = 0x00;
	while (!(SPI1->SR&SPI_SR_RXNE));
	//return  (Spi1_DR_8bit) ;	
	return static_cast <uint8_t>(SPI1->DR);	
}

uint16_t Spi::receive_16 ()
{
	SPI1->DR = 0xFFFF;
	while (!(SPI1->SR&SPI_SR_RXNE));
	return SPI1->DR;	
}

uint16_t Spi::receive ()
{
	 return (this->*(Spi::ptr_receive[size_]))();
}


uint16_t Spi::exchange_8 (uint16_t data)
{
	while (SPI1->SR&SPI_SR_BSY);
	*(uint8_t *)&(SPI1->DR) = static_cast <uint8_t> (data);
	while (!(SPI1->SR&SPI_SR_RXNE));
	return static_cast <uint8_t>(SPI1->DR);
}
uint16_t Spi::exchange_16 (uint16_t data)
{
	while (SPI1->SR&SPI_SR_BSY);
	SPI1->DR = data;
	while (!(SPI1->SR&SPI_SR_RXNE));
	return SPI1->DR;	
}
uint16_t Spi::exchange (uint16_t data)
{
	return (this->*(Spi::ptr_exchange[size_]))(data);
}

