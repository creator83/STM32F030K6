#include "stm32f0xx.h"
#include "gpio.h"
#include "gtimer.h"
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

	enum mode {EdgePwm, CenterPwm1, CenterPwm2, CenterPwm3};
	enum pulseMode {highPulse, lowPulse};
	enum inverse {off=6, on};

private:
	typedef void(Pwm::*PtrPwm)(Pwm::pulseMode);
	Gpio pwmPin;
	Gtimer * timer;
	Gtimer::nChannel pwmChannel;
	TIM_TypeDef * ptrTimer;
	static uint8_t ccrPtr [4];
	static PtrPwm funcMode [3];

public:
	Pwm (Gtimer &, Gpio::Port, uint8_t pin_, Gpio::Afmode af, Gtimer::nChannel ch, mode, pulseMode, inverse = off);
	void setValue (uint16_t);
	void start ();
	void stop ();
private:
	void setMode ();
	void setEdgePwm (pulseMode m);
	void setCenterPwm ();
	void setCombinePwm ();

};



#endif
