#include "stm32f0xx.h"                  // Device header
#include "tact.h"

#ifndef SYSTIMER_H
#define SYSTIMER_H


class systimer
{
	//variables
public:
	enum mode {us, ms, hz };
	
private:
	
//functions
public:
	systimer (mode m, uint16_t val);

private:
	
};

#endif
