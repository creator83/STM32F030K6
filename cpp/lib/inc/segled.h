#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"
#include "timer14.h"

#ifndef SEGLED_H
#define SEGLED_H

class segled
{
//variables
public:	
	enum Port {A , B , C , F=5};
	enum Segment {a, b, c, d, e, f, g, dp};
	enum Digit {first, second, third, fourth};
private:
	timer14 timer;
	Gpio pin_segment;
	Gpio pin_digit;
	bool flag;
	static char number [11];
//functions
public:	
	segled (Port seg, Port dig);
	void OFF ();
private:
friend void TIM14_IRQHandler();
};

void TIM14_IRQHandler();


#endif
