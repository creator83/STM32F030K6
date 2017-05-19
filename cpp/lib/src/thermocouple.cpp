#include "thermocouple.h"



 
 
Thermocouple::Thermocouple (uint16_t k_)
:k(k_)
{
  for (uint8_t i=0;i<41;++i)
 {
  adcGrid[i] = typeK::adcGrid[i]*k;
 }
 for (uint8_t i=0;i<40;++i)
 {
  delta [i] = adcGrid [i+1] - adcGrid [i];
 }
}

uint16_t Thermocouple::calcDec (uint16_t val)
{
  int8_t grid = 0;
  uint32_t tVal = val*806; 
  for (uint8_t i=0;i<41;++i)
  {
    if (tVal>adcGrid[i]) ++grid; 
  }
  uint32_t temp = (tVal - adcGrid[grid-1])*100;
  temp /= delta [grid-1];
  temp += grid*100;
  return temp;
}

uint8_t Thermocouple::calc (uint16_t val)
{
  int8_t grid = 0; 
  for (uint8_t i=0;i<16;++i)
  {
    if (val>adcGrid[i]) ++grid; 
  }
  uint16_t temp = (adcGrid[grid-1]-val)*10;
  temp /= delta [grid-1];
  temp += grid*10;
  return temp;
}

