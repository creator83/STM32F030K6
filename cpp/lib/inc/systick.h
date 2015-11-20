#include "stm32f0xx.h"                  // Device header
#include "tact.h"

#ifndef TIMER14_H
#define TIMER14_H


class timer14
{
	//variables
public:
	enum mode {us, ms, hz , prsk};
	enum intrpt {Update, Compare};
	
	
private:
	
//functions
public:
	timer14 (uint16_t val, mode m);
	//timer14 (uint16_t us);
	//timer14 (uint8_t khz);
	void Set_CNT (uint16_t);
	uint16_t Get_CNT ();
	void Set_ARR (uint16_t);
	void interrupt (intrpt i);
	void Start ();
	void Stop ();
	void ClearFlag();

private:
	
};

#endif
