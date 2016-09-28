#include "Spi.h"

SPI_TypeDef * Spi::SpiBase [2] = {SPI1, SPI2};

PotMemFn Spi::ptr_receive[2] = {&Spi::receive_8, &Spi::receive_16};

PotMemF Spi::ptr_transmite[2] = {&Spi::transmit_8, &Spi::transmit_16};
ptr_ex Spi::ptr_exchange[2] =  {&Spi::exchange_8, &Spi::exchange_16};


Spi::Spi (Role r)
{
  //tact Spi1
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
  
  //===Settings pins===//

  //CS
  pin.setOutPin (pins_d[p][CS]);


  //SCK
  pin.setOutPin (pins_d[p][SCK] , Gpio::AltFunc, Gpio::High );
    
  //MOSI
  pin.setOutPin(pins_d[p][MOSI]  , Gpio::AltFunc, Gpio::High );
  
  //MISO
  pin.setOutPin (pins_d[p][MISO]  , Gpio::AltFunc);
  
  Set_CS ();
  
  
  //===Settings Spi===//
  

  //Mode Master/Slave
  Spi1->CR1 |= r << 2;
    
  // CPOL
  Spi1->CR1 |= cpl << 1;
  
  //CPHA
  Spi1->CR1 |= cph << 0;
  
  // Division
  Spi1->CR1 |= div << 3;
	
	//Data size
	Spi1->CR2 &= ~Spi_CR2_DS;
	Spi1->CR2 |= 7 << 8;
	Spi1->CR2 |= s << 11;
  
  //Soft mode  
   Spi1->CR1 |= Spi_CR1_SSM ;
   Spi1->CR1 |= Spi_CR1_SSI ;
	 Spi1->CR2 |= Spi_CR2_SSOE;
	
	if (s == bit8) Spi1->CR2 |= Spi_CR2_FRXTH;
   
	 //Turn on Spi1
   Spi1->CR1 |= Spi_CR1_SPE;
}

void Spi::Set_CS ()
{
  pin.setPin (pins_d[port_][CS]);
}

void Spi::Clear_CS ()
{
  pin.clearPin (pins_d[port_][CS]);
}

void Spi::transmit_8 (uint16_t data)
{
	while (!(Spi1->SR&Spi_SR_TXE));
	*(uint8_t *)&(Spi1->DR) = static_cast <uint8_t> (data);
	while (Spi1->SR&Spi_SR_BSY);
}

void Spi::transmit_16 (uint16_t data)
{
	while (!(Spi1->SR&Spi_SR_TXE));
	Spi1->DR = data;
	while (Spi1->SR&Spi_SR_BSY);
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
	*(uint8_t *)&(Spi1->DR) = 0x00;
	while (!(Spi1->SR&Spi_SR_RXNE));
	//return  (Spi1_DR_8bit) ;	
	return static_cast <uint8_t>(Spi1->DR);	
}

uint16_t Spi::receive_16 ()
{
	Spi1->DR = 0xFFFF;
	while (!(Spi1->SR&Spi_SR_RXNE));
	return Spi1->DR;	
}

uint16_t Spi::receive ()
{
	 return (this->*(Spi::ptr_receive[size_]))();
}


uint16_t Spi::exchange_8 (uint16_t data)
{
	while (Spi1->SR&Spi_SR_BSY);
	*(uint8_t *)&(Spi1->DR) = static_cast <uint8_t> (data);
	while (!(Spi1->SR&Spi_SR_RXNE));
	return static_cast <uint8_t>(Spi1->DR);
}
uint16_t Spi::exchange_16 (uint16_t data)
{
	while (Spi1->SR&Spi_SR_BSY);
	Spi1->DR = data;
	while (!(Spi1->SR&Spi_SR_RXNE));
	return Spi1->DR;	
}
uint16_t Spi::exchange (uint16_t data)
{
	return (this->*(Spi::ptr_exchange[size_]))(data);
}

