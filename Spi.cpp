#include "spi.h"

spi::spi(Division div, Cpol cpl, Cpha cph, Role r)
:pin (Gpio::A)
{
  //Включение тактирования SPI
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
  
  //===настройка выходов/входов===//

  //CS
  pin.setOutPin (CS);


  //SCK
  pin.setOutPin (SCK , Gpio::AltFunc , Gpio::High);
    
  //MOSI
  pin.setOutPin(MOSI , Gpio::AltFunc , Gpio::High);
  
  //MISO
  pin.setOutPin (MISO , Gpio::AltFunc);
  
  Set_CS ();
  
  
  //===Настройка модуля SPI===//
  
  //очистка
  SPI1->CR1 = 0;

  //режим Master/Slave
  SPI1->CR1 |= r << 2;
    
  // CPOL
  SPI1->CR1 |= cpl << 1;
  
  //CPHA
  SPI1->CR1 |= cph << 0;
  
  // настройка скорости
  SPI1->CR1 |= div << 3;
  
  //Soft mode  
   SPI1->CR1 |= SPI_CR1_SSM ;
   SPI1->CR1 |= SPI_CR1_SSI ;

   //Включение
   SPI1->CR1 |= SPI_CR1_SPE;


}

void spi::Set_CS ()
{
  pin.setPin (CS);
}

void spi::Clear_CS ()
{
  pin.clearPin (CS);
}

uint8_t spi::transfer (uint8_t data)
{
  SPI1->DR = data << 8;
  while (SPI1->SR&SPI_SR_BSY);
  return static_cast <uint8_t> (SPI1->DR);
}


