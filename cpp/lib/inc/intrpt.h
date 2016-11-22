#include "stm32f0xx.h"                  // Device header
#include "pin.h"


#ifndef INTRPT_H
#define INTRPT_H

typedef uint32_t * reg;

class Intrpt
{
  //variables
public:
	enum sense {Rising_edge = 1, Falling_edge, RiseFall};



protected:
private:

//static unsigned int pAdr [3];	
  Pin pin_;
  
//functions
public:
  Intrpt(Gpio::Port p , uint8_t pin_, sense s);
};



#endif
