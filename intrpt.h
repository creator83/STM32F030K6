#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"


#ifndef INTRPT_H
#define INTRPT_H

typedef uint32_t * reg;

class intrpt
{
  //variables
public:
  enum Port {A , B , C , D, F=5};
	enum sense {Rising_edge = 1, Falling_edge, RiseFall};



protected:
private:

//static unsigned int pAdr [3];	
  Gpio pin;
  
//functions
public:
  intrpt(Port p , uint8_t pin_, sense s);
	intrpt(uint8_t p , uint8_t pin_, sense s);
};



#endif
