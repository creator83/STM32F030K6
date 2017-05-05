#include "senc.h"


Senc::Senc (Gpio::Port pA, uint8_t pinA, Gpio::Port pB, uint8_t pinB)
:pha (pA, pinA, Gpio::PP::PullDown), phb (pB, pinB, Gpio::PP::PullDown)
{
  low = 0;
  delta = 1;
}


Senc::Senc (Gpio::Port pA, uint8_t pinA, Gpio::Port pB, uint8_t pinB,uint16_t range)
:pha (pA, pinA, Gpio::PP::PullDown), phb (pB, pinB, Gpio::PP::PullDown)
{
  high = range << 1;
  low = 0;
  delta = 1;
}

uint16_t Senc::getValue ()
{
  return value >> 1;
}

void Senc::setValue  (uint16_t val)
{
  value = val << 1;
}

void Senc::scan ()
{
  uint8_t new_;
  new_ = (1 << pha.state())|phb.state();
  switch (previusState)
  {
    case 2:
    {
    if (new_ == 3&&value==high);
    if (new_ == 3&&value<high)value+=delta;
    if (new_ == 0&&value==low);
    if (new_ == 0&&value>low) value-=delta;
    break;
    }
    case 0:
    {
    if (new_ == 2&&value==high);
    if (new_ == 2&&value<high)value+=delta;
    if (new_ == 1&&value==low);
    if (new_ == 1&&value>low) value-=delta;
    break;
    }
    case 1:
    {
    if (new_ == 0&&value==high);
    if (new_ == 0&&value<high)value+=delta;
    if (new_ == 3&&value==low);
    if (new_ == 3&&value>low) value-=delta;
    break;
    }		
    case 3:
    {
    if (new_ == 1&&value==high);
    if (new_ == 1&&value<high)value+=delta;
    if (new_ == 2&&value==low);
    if (new_ == 2&&value>low) value-=delta;
    break;
  }				
  }
  previusState = new_;
}

void Senc::setHigh (uint16_t v)
{
	high = v << 1;
}

void Senc::setLow (uint16_t v)
{
	low = v << 1;
}

void Senc::setGrade (uint16_t val)
{
	delta = val;
}

