#include "stm32f0xx.h"                  // Device header
#include "gpio.h"


#ifndef BUTTON_H
#define BUTTON_H

class button
{
//variables
public:
	enum PORT {A, B, C, D};
	uint16_t count;
	bool short_press;
	bool long_press;
	bool push_l_state;
	bool push_state;
	bool act_state;
	bool debouncer;
	uint8_t sh_press_lmt;
	uint8_t long_press_lmt;
	uint8_t p;
	Gpio pin;
//func
	button (PORT p_, uint8_t pin_);
	void scan_short ();
	void action_short (void (*func)());
	void action_long (void (*func)());
};

#endif
