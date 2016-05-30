#include "stm32f0xx.h"                  // Device header
#include "tact.h"

#ifndef GENERAL_TIMER_H
#define GENERAL_TIMER_H

class general_timer;

typedef void (general_timer::*PotMemFn)() ;

class general_timer
{
	//variables
public:
	enum mode {PWM, ENCODER, OPM_OUTPUT, OUTPUT, INPUT};
	enum timers {TIM_3, TIM_14, TIM_15, TIM_16, TIM_17};
	enum interrupt {Off, On};
	
private:
	static PotMemFn init [5];
	static uint32_t bases [5];
	static uint8_t intrpt [5];
	uint8_t tmr;
//functions
public:
	general_timer (uint8_t t);
	general_timer (timers t, uint16_t psc, uint16_t arr);
	general_timer (timers t);
	void timer3_init ();
	void timer14_init ();
	void timer15_init ();
	void timer16_init ();
	void timer17_init ();
	void output_mode ();
	void set_interrupt (int8_t pr);
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
