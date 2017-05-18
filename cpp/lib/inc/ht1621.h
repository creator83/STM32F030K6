#include "device.h"                // Device header
#include "pin.h"
#include "spi.h"
#include "delay.h"

#ifndef HT1621_H
#define HT1621_H

namespace ht1621Command
{
 uint16_t lcdOff = 0x804;
 uint16_t lcdOfn = 0x806;
 
}
class Ht1621
{
//variables
public:	
   enum class bias {};
   enum class mode {command = 4, write, read};
private:
  Spi * spiDriver;
  Pin cs;
  Pin * sck, *mosi;
public:	
  Ht1621 (Gpio::Port, uint8_t, Spi &, Pin & sck_, Pin & mosi_);
  void address (uint8_t);
  void data (uint8_t);
  void chipAssert ();
  void chipDisassert ();
  void command (uint16_t);
  void sendByte (uint8_t comm, uint8_t dta);
  void refrash (uint8_t *);
private:
	
  void init();
};


#endif


