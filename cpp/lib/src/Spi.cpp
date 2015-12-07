#include "spi.h"

uint8_t spi::pins_d[2][4]={{4,5,6,7},{6,3,4,5}};


spi::spi(PORT p, Division div, Cpol cpl, Cpha cph, Role r, Size s)
:pin (p)
{
	port_ = p;
  //tact SPI1
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
  
  //===Settings pins===//

  //CS
  pin.setOutPin (pins_d[p][CS]);


  //SCK
  pin.setOutPin (pins_d[p][SCK] , Gpio::AltFunc , Gpio::High);
    
  //MOSI
  pin.setOutPin(pins_d[p][MOSI]  , Gpio::AltFunc , Gpio::High);
  
  //MISO
  pin.setOutPin (pins_d[p][MISO]  , Gpio::AltFunc);
  
  Set_CS ();
  
  
  //===Settings SPI===//
  

  //Mode Master/Slave
  SPI1->CR1 |= r << 2;
    
  // CPOL
  SPI1->CR1 |= cpl << 1;
  
  //CPHA
  SPI1->CR1 |= cph << 0;
  
  // Division
  SPI1->CR1 |= div << 3;
	
	//Data size
	SPI1->CR2 &= ~SPI_CR2_DS;
	SPI1->CR2 |= s << 8;
  
  //Soft mode  
   SPI1->CR1 |= SPI_CR1_SSM ;
   SPI1->CR1 |= SPI_CR1_SSI ;
	// SPI1->CR2 |= SPI_CR2_SSOE;
   
	 //Turn on spi1
   SPI1->CR1 |= SPI_CR1_SPE;
}

void spi::Set_CS ()
{
  pin.setPin (pins_d[port_][CS]);
}

void spi::Clear_CS ()
{
  pin.clearPin (pins_d[port_][CS]);
}

void spi::transmit_8 (uint8_t data)
{
	while (SPI1->SR&SPI_SR_BSY);
	*(uint8_t *)&(SPI1->DR) = data;
}

uint8_t spi::receive_8 ()
{
	*(uint8_t *)&(SPI1->DR) = 0x00;
	while (!(SPI1->SR&SPI_SR_RXNE));
	return static_cast <uint8_t>(SPI1->DR);	
}

uint16_t spi::receive_16 ()
{
	SPI1->DR = 0x0000;
	while (!(SPI1->SR&SPI_SR_RXNE));
	return SPI1->DR;	
}

