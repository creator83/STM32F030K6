#include "max6675.h"

char max6675::number [10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

#ifdef SOFTSPI
max6675::max6675(PORT p, int8_t SCLK, int8_t CS, int8_t MISO)
:pin (p)
{
  sclk = SCLK;
  cs = CS;
  miso = MISO;
  pin.setOutPin(sclk);
  pin.setOutPin(cs);
  //pin.setPin (sclk);
  pin.setPin (cs);
}

uint16_t max6675::spiread()
{
  uint8_t data = 0;

  for (int8_t i=15; i>=0; i--)
  {
    
    if (GPIOA->IDR & (1 << miso)) 
      {
				pin.setPin(sclk);
				delay_ms(1);
      //set the bit to 0 no matter what
      data |= (1 << i);
      }
		pin.clearPin(sclk);
		delay_ms (1);
  }
  return data;
}

void max6675::readTemp()
{
  pin.clearPin(cs);
  delay_ms (1);
  byteCode.code16 = spiread();
  pin.setPin (cs);
  byteCode.code16 >>= 3;
  t = static_cast <double> (byteCode.code16*0.25);
}

void max6675::buffer (double val)
{
	char dec, ones, decimal;
	dec = val/10;
	buff[0] = number [dec];
	ones = (int)val%10;
	buff[1] = number [ones];
	decimal = (int)(val*10)%10;
	buff[3] = number [decimal];
}
#else 


max6675::max6675()
:spi1 (spi::div32)
{
	spi1.Set_CS();
} 

uint16_t max6675::getCode()
{
  spi1.Clear_CS();
  delay_ms (1);
  byteCode.code8[1] = spi1.transfer(0);
  byteCode.code8[0] = spi1.transfer(0);
  spi1.Set_CS ();
  byteCode.code16 >>= 3;
  return byteCode.code16;
}

#endif

