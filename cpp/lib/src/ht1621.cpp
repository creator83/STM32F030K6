#include "ht1621.h"



Ht1621::Ht1621 (Gpio::Port p, uint8_t n, Spi &d, Pin & sck_, Pin & mosi_)
:spiDriver (&d), cs(p, n, Gpio::Omode::PushPull), sck (&sck_), mosi (&mosi_)
{
  init ();
  
}

void Ht1621::init()
{
 cs.set ();
 spiDriver->setBaudrate (Spi::division::div256);
 spiDriver->setCpha (Spi::cpha::first);
 spiDriver->setCpol (Spi::cpol::neg);
 spiDriver->setFsize (Spi::fsize::bit_4);
 spiDriver->start ();
}

void Ht1621::chipAssert ()
{
  cs.clear ();
}

void Ht1621::chipDisassert ()
{
  cs.set ();
}

void Ht1621::command (uint16_t comm)
{
  spiDriver->setFsize (Spi::fsize::bit_9);
  chipAssert ();
  spiDriver->putData (comm);
  delay_ms (1);
  chipDisassert ();
}

void Ht1621::sendByte (uint8_t addr, uint8_t dta)
{
 spiDriver->setFsize (Spi::fsize::bit_14);
 uint16_t temp = (static_cast <uint8_t> (mode::write) << 12|addr << 5|dta << 1);
 chipAssert ();
 spiDriver->putData (temp);
 delay_ms (1);
 chipDisassert ();
}

void Ht1621::refrash (uint8_t * buffer)
{
 spiDriver->setFsize (Spi::fsize::bit_9);
 uint16_t temp = static_cast <uint8_t> (mode::write) << 6;
 chipAssert (); 
 spiDriver->putData (temp);
 spiDriver->setFsize (Spi::fsize::bit_4);
 for (uint8_t i=0;i<32;++i)
 {
   spiDriver->putData (buffer[i]);
 }
 delay_ms (1);
 chipDisassert ();
}
