#include "max6675.h"

char max6675::number [10] = {'0','1','2','3','4','5','6','7','8','9'};

max6675::max6675 ()
:spi1(spi::A, spi::div256, spi::neg, spi::second,spi::master, spi::bit16)
{
}

uint16_t max6675::readCelsius()
{
	uint16_t v;
	spi1.Clear_CS();
	delay_ms (200);
	v = spi1.receive_16();
	//v = spi1.receive();
	spi1.Set_CS();
	  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }
	v>>=5;
	return v;	
}



void max6675::buffer (uint16_t t)
{
	char dec, ones;
	uint16_t temp = t;
	
	for (dec=0;temp>=10;++dec)temp -=10;

	for (ones=0;temp>=1;++ones)temp--;
	
	buffer_value [0]= number [dec];
	buffer_value [1]= number [ones];
}


