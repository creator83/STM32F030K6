#include "device.h"                // Device header
 

#ifndef LMT84_H
#define LMT84_H


class Lmt84
{
//variables
 
public:	
private:
 static uint16_t adcGrid [16];
 static uint8_t delta [15];
public:	
  Lmt84 ();
  uint16_t calcDec (uint16_t);
  uint8_t calc (uint16_t);
private:
	
  
};


#endif


