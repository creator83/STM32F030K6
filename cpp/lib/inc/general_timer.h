#include "stm32f0xx.h"                  // Device header
#include "tact.h"

#ifndef GENERAL_TIMER_H
#define GENERAL_TIMER_H

class general_timer
{
	//variables
public:
	enum mode {PWM, ENCODER, OPM_OUTPUT, OUTPUT, INPUT};
	
private:
//functions
public:
	general_timer (mode m);
	void Set_CNT (uint16_t);
	void Set_PSC (uint16_t);
	void Set_ARR (uint16_t);
	uint16_t Get_CNT ();
	void Start ();
	void Stop ();
	void ClearFlag();

private:
	
};
 
#endif
