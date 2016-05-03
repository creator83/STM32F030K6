#include "button.h"

button::button (PORT p_, uint8_t pin_)
:pin (p_)
{
	pin.setInPin (pin_);
	p = p_;
}

void button::scan_short ()
{
	if (push_state)
	{
		if (pin.PinState(p))
		{
			short_press = true;
			push_state = false;
		}
	}
	else
	{
			if (!pin.PinState(p)) push_state = true;
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
