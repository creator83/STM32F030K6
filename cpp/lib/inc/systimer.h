#include "device.h"                // Device header
#include "tact.h"

#ifndef SYSTIMER_H
#define SYSTIMER_H


class Systimer
{
	//variables
public:
	enum class mode {us, ms, hz };
	
private:
	
//functions
public:
	Systimer (mode m, uint16_t val);
	void interruptEnable ();
	void interruptDisable ();

private:
	
};

#endif
