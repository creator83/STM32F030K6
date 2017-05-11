#include "device.h"  
#include "pin.h"
#include "gtimer.h"
#include "atimer.h"

/*
 * TIM3
 * PHA - PTA6 (Af1)
 * PHB - PTA7 (Af1)
 * PHA - PTB4 (Af1)
 * PHB - PTB5 (Af1)
 
 * TIM1
 * PHA - PTA8 (Af2)
 * PHB - PTA9 (Af2)
 */

namespace QdDef
{
//===Defenitions===//
//PHA
 const Gpio::Port PhaPort = Gpio::Port::A;
 const Gpio::Afmode PhaAf = Gpio::Afmode::AF2;
const uint8_t PhaPin = 8;

//PHB
 const Gpio::Port PhbPort = Gpio::Port::A;
const Gpio::Afmode PhbAf = Gpio::Afmode::AF2;
const uint8_t PhbPin = 9;
}




#ifndef QENC_H
#define QENC_H


class Qenc
{
  //variables
public:

private:
	Pin pha, phb;
	uint16_t high;
	uint16_t value;
	TIM_TypeDef * ptrTimer;
	Gtimer * gtimer;
	Atimer * atimer;

public:
	Qenc (uint16_t range);
	Qenc (Gtimer &, uint16_t range);
	Qenc (Atimer &, uint16_t range=100);
	uint16_t getValue ();
	void setValue  (uint16_t);
	void start ();
	void stop ();

private:
	void setMode ();
};



#endif
