#include "stm32f0xx.h"
#include "gpio.h"
#include "gtimer.h"

namespace PwmDef
{
//===Defenitions===//
//pwm
const Gpio::Port PwmPort = Gpio::B;
const uint8_t PwmPin = 0;
const Gpio::Afmode PwmAlt = Gpio::AF1;	
const Gtimer::nChannel PwmCh = Gtimer::channel3;
}




#ifndef PWM_H
#define PWM_H

class Pwm;



class Pwm : public Gtimer
{
  //variables
public:

	enum mode {EdgePwm, CenterPwm1, CenterPwm2, CenterPwm3};
	enum pulseMode {highPulse, lowPulse};
	enum inverse {off=6, on};

private:
	
	Gpio pin;


public:
	Pwm (nTimer n_, nChannel ch, mode, pulseMode, inverse);


private:
	void setMode ();

};



#endif
