#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"

#ifndef SEGLED_H
#define SEGLED_H

class segled
{
//variables
public:	
	enum Port {A , B , C , F=5};
	enum Segment {a=0, b=1, c=3, d, e, f, g, dp};
	enum Digit {first, second, third, fourth};
	char buffer [4];
private:
	Gpio pin_segment;
	Gpio pin_digit;
	static char number [11];
	char pins [4];
	char n;
//functions
public:	
	segled (Port seg, Port dig);
	void OFF ();
	void get_buffer (uint16_t val);
	void digit ();
private:
	
	void frame (uint8_t dig);
};


#endif
