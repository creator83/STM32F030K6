#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"
#include "spi.h"

#define SOFTSPI
#ifndef MAX6675_H
#define MAX6675_H

class max6675
{
//variables
public:
	enum Port {A , B , C , F=5};
private:
#ifdef SOFTSPI	
  Gpio pin;
#else
  spi spi1;
#endif
	uint8_t sck,miso, cs;

//functions
public:
#ifdef SOFTSPI
	max6675 (Port p, uint8_t _sck, uint8_t _miso, uint8_t _cs);

#else
	max6675 ();
	
#endif
};
#endif
