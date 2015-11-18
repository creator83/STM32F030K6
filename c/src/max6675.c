#include "max6675.h"
#include "spi.h"

#ifdef SPI_16
void max6675_init (void)
{
	init_spi_16 ();
}

uint16_t readCelsius(void)
{
  uint16_t v;

  clear_cs ();
  delay_ms(1);

  v = spi1_rx_16();

  set_cs ();

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }

  v >>= 5;
	
  return v;
}
#else
void max6675_init (void)
{
	init_spi_8 ();
}

uint16_t readCelsius(void)
{
  uint16_t v;

  clear_cs ();
  delay_ms(1);
  v = spi1_rx_8();
	v <<= 8;
	v |= spi1_rx_8();
  set_cs ();

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }

  v >>= 5;
	
  return v;
}

#endif

/*
double readCelsius(void)
{
  uint16_t v;

  clear_cs ();
  delay_ms(1);

  v = spi1_rx_16();

  set_cs ();

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return 0; 
    //return -100;
  }

  v >>= 3;
	//v >>= 2;
  return v*0.25;
}*/




/*
void max6675_buffer (uint16_t val)
{
	char dec, ones;
	dec = division (val);
	max6675_buff[0] = max6675_number [dec];
	ones = val%10;
	max6675_buff[1] = max6675_number [ones];
}

uint16_t division (uint16_t n)
{
	uint32_t quot, qq;
	uint8_t rem;
// Multiplay 0.8	
	quot = n >> 1;
  quot += quot >> 1;
  quot += quot >> 4;
  quot += quot >> 8;
  quot += quot >> 16;
  qq = quot;
// devision 8
  quot >>= 3;
//calculate rem
  rem = (uint8_t)(n - ((quot << 1) + (qq & ~7ul)));
// correct
    if(rem > 9)
    {
        rem -= 10;
        quot++;
    }
    return quot;

}*/









