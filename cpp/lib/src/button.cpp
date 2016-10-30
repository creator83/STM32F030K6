#include "button.h"

Button::Button (Gpio::Port p_, uint8_t pin_)
:pin (p_)
{
	/*shortFunction = nullptr;
	longFunction = nullptr;	*/
	pin.settingPin (pin_, Gpio::Input);
	p = pin_;
	shortPress = longPress = lastState = currentState = false;
	counter = 0;
	longLimit = 0xFFFF;
}

void Button::scan ()
{
	if (!pin.pinState (p)&&!shortPress&&!longPress)
	{
		currentState = !pin.pinState (p);
		state = lastState << 1| currentState;
		switch (state)
		{
			case 1:
				counter++;
			break;
			case 2:
				counter = 0;
			break;
			case 3:
				counter++;
			break;
		}
		lastState = currentState;
	}
	if (counter>shortLimit && counter<longLimit && pin.pinState(p))
	{
		shortPress = 1;
		counter = 0;
	}
	if (counter>longLimit)
	{
		longPress = 1;
		counter = 0;
	}
	if (longPress) 
	{
		longFunction();
		do
			longPress = 0;
		while (!pin.pinState (p));
	}
	if (shortPress)
	{
		shortFunction ();
		shortPress = 0;
	}
}

void Button::setShortLimit (uint16_t val)
{
	shortLimit = val;	
}
void Button::setLongLimit (uint16_t val)
{
	longLimit = val;
}
		
void Button::setshortPressAction (void (*f)())
{
	shortFunction = f;
}

void Button::setlongPressAction (void (*f)())
{
	longFunction = f;
}

