#include "button.h"

button::button (PORT p_, uint8_t pin_)
:pin (p_)
{
	pin.setInPin (pin_);
	p = p_;
	sh_press_lmt = 2;
}

void button::scan_short ()
{
	if (!debouncer)
	{
		if (push_state)
		{
			if (!pin.PinState(p)) count ++;
			if (pin.PinState(p)&&count>sh_press_lmt)
			{
				count = 0;
				push_state = false;
				short_press = true;
			}
		}
		else
		{
			if (!pin.PinState(p)) push_state = true;
		}
	}
	else count ++;
	if (debouncer&&count>5)
	{
		debouncer = false;
		count = 0;
	}		
}

void button::action_short (void (*func)())
{
	short_press = false;	
	func();
}

void button::action_long (void (*func)())
{
	
}
