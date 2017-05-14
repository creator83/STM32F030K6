#include "device.h"  
#include "pin.h"
#include "gtimer.h"
#include "atimer.h"
/*
namespace PwmDef
{
//===Defenitions===//
//pwm
const Gpio::Port PwmPort = Gpio::B;
const uint8_t PwmPin = 0;
const Gpio::Afmode PwmAlt = Gpio::AF4;	
const Gtimer::nChannel PwmCh = Gtimer::channel3;
}*/




#ifndef PWM_H
#define PWM_H

class Pwm;



class Pwm 
{
  //variables
public:

	enum class mode {EdgePwm, CenterPwm1, CenterPwm2, CenterPwm3};
	enum class pulseMode {highPulse, lowPulse};
	enum class inverse {off=6, on};

private:
	typedef void(Pwm::*PtrPwm)(Pwm::pulseMode);
	Pin *pwmPin;
	Gtimer * timer;
	Atimer * timer1;
	uint8_t pwmChannel;
	TIM_TypeDef * ptrTimer;
	static uint8_t ccrPtr [4];
	static PtrPwm funcMode [3];

public:
	
	Pwm (Gtimer &, Pin &, Gtimer::nChannel ch, mode = mode::EdgePwm, pulseMode = pulseMode::highPulse, inverse = inverse::off);
	Pwm (Atimer &, Pin &, Gpio::Afmode af, Gtimer::nChannel ch, mode, pulseMode, inverse = inverse::off);
	void setValue (uint16_t);
	void setPeriod (uint16_t);
	void start ();
	void stop ();
private:
	void setMode ();
	void setEdgePwm (pulseMode m);
	void setCenterPwm ();
	void setCombinePwm ();

};



#endif
