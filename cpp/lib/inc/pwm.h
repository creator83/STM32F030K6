#include "stm32f0xx.h"
#include "gpio.h"
#include "gtimer.h"

namespace PwmDef
{
//===Defenitions===//
//CS
const Gpio::Port PwmPort = Gpio::C;
const uint8_t PwmPin = 1;
}




#ifndef PWM_H
#define PWM_H

class Pwm;

typedef void(Pwm::*PtrPwm)(Pwm::pulseMode) ;

class Pwm : public Gtimer
{
  //variables
public:

	enum mode {EdgePwm, CenterPwm1, CenterPwm2, CenterPwm3};
	enum pulseMode {highPulse, lowPulse};


private:
	
	Gpio pin;
	static PtrPwm funcMode [3];


public:
	Pwm (nTimer n_, nChannel ch, mode, pulseMode);


private:
	void setMode ();
	void setEdgePwm (pulseMode m);
	void setCenterPwm ();
	void setCombinePwm ();

};



#endif
