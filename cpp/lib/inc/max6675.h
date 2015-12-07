#include "stm32f0xx.h"                  // Device header
#include "spi.h"


#ifndef MAX6675_H
#define MAX6675_H

class max6675
{
//variables
public:

	char buffer_value[2];
private:
  spi spi1;
	static char number [10];

//functions
public:
	max6675 ();
	uint16_t readCelsius();
	void buffer (uint16_t t);
};
#endif
