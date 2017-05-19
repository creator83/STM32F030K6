#include "lmt84.h"

uint16_t  Lmt84::adcGrid [16] = {1283, 1216, 1148, 1081, 1013, 943, 874, 803, 733, 663, 591, 520, 448, 375, 302, 227};
uint8_t  Lmt84::delta [15] = {67, 68, 67, 68, 69, 69, 71, 69, 71, 72, 71, 72, 73, 73, 74};

 
 
 Lmt84::Lmt84 ()
 {
 }

uint16_t Lmt84::calcDec (uint16_t val)
{
  int8_t grid = 0; 
  for (uint8_t i=0;i<16;++i)
  {
    if (val<adcGrid[i]) ++grid; 
  }
  uint16_t temp = (adcGrid[grid-1]-val)*100;
  temp /= delta [grid-1];
  temp += grid*100;
  return temp;
}

uint8_t Lmt84::calc (uint16_t val)
{
  int8_t grid = 0; 
  for (uint8_t i=0;i<16;++i)
  {
    if (val<adcGrid[i]) ++grid; 
  }
  uint16_t temp = (adcGrid[grid-1]-val)*10;
  temp /= delta [grid-1];
  temp += grid*10;
  return temp;
}

