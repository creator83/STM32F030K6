#include "stm32f0xx.h"   
#include "gpio.h"
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
const Gpio::Port PhaPort = Gpio::B;
const Gpio::Afmode PhaAf = Gpio::AF1;
const uint8_t PhaPin = 4;

//PHB
const Gpio::Port PhbPort = Gpio::B;
const Gpio::Afmode PhbAf = Gpio::AF1;
const uint8_t PhbPin = 5;
}




#ifndef QENC_H
#define QENC_H


class Qenc : public Gtimer
{
  //variables
public:

private:
	Gpio pha, phb;
	uint16_t high;
	uint16_t value;

public:
	Qenc (uint16_t range);
	uint16_t getValue ();

private:
	void setMode ();
};



#endif
