#include "stm32f0xx.h"   
#include "pin.h"
#include "gtimer.h"

/*
 * TIM3
 * PHA - PTA6 (Af1)
 * PHB - PTA7 (Af1)
 * PHA - PTB4 (Af1)
 * PHB - PTB5 (Af1)
 */

namespace QdDef
{
//===Defenitions===//
//PHA
const Gpio::Port PhaPort = Gpio::A;
const Gpio::Afmode PhaAf = Gpio::AF1;
const uint8_t PhaPin = 6;

//PHB
const Gpio::Port PhbPort = Gpio::A;
const Gpio::Afmode PhbAf = Gpio::AF1;
const uint8_t PhbPin = 7;
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
	Gtimer * timer;

public:
	Qenc (uint16_t range);
	Qenc (Gtimer &, uint16_t range);
	uint16_t getValue ();
	void setValue  (uint16_t);
	void start ();
	void stop ();

private:
	void setMode ();
};



#endif
