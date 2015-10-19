#include "max6675.h"



#ifdef SOFTSPI
max6675::max6675(PORT p, int8_t SCLK, int8_t CS, int8_t MISO)
:pin (p)
{
  sclk = SCLK;
  cs = CS;
  miso = MISO;
  pin.setOutPin(sclk);
  pin.setOutPin(cs);
  pin.setPin (sclk);
  pin.setPin (cs);
}

uint8_t max6675::spiread()
{
  uint8_t data = 0;

  for (int8_t i=7; i>=0; i--)
  {
    pin.setPin(sclk);
    delay_ms(1);
    if (GPIOA->IDR & (1 << miso)) 
      {
      //set the bit to 0 no matter what
      data |= (1 << i);
      }
  }
  return data;
}

uint16_t max6675::getCode()
{
  pin.clearPin(cs);
  delay_ms (1);
  byteCode.code8[1] = spiread();
  byteCode.code8[0] = spiread();
  pin.setPin (cs);
  byteCode.code16 >>= 3;
  return byteCode.code16;
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


uint8_t max6675::getTemp()
{
  double c = getCode()*0.25;
  return static_cast <uint8_t>(c);
}