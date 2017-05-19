#include "device.h"                // Device header
 

#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H

namespace typeK
{
 const uint16_t vGrid = 806;
 const uint16_t adcGrid [41] = {0, 397, 798, 1203, 1612, 2023, 2436, 2851, 3267, 3682, 4096, 4509, 4920, 5328, 5735, 6138, 6540, 6941, 7340, 7739, 8138, 8539, 8940, 9343, 9747, 10153, 10561, 10971, 11382, 11795, 12209, 12624, 13040, 13457, 13874, 14293, 14713, 15133, 15554, 15975, 16397};
}
class Thermocouple
{
//variables
 
public:	
private:
 uint16_t k;
 uint32_t adcGrid [41];
 uint16_t delta [40];
public:	
  Thermocouple (uint16_t);
  uint16_t calcDec (uint16_t);
  uint8_t calc (uint16_t);
private:
	
  
};


#endif


