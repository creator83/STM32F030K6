#include "button.h"

Button::Button (Gpio::Port p_, uint8_t pin_)
:pin (p_, pin_, Gpio::NoPP)
{
	/*shortFunction = nullptr;
	longFunction = nullptr;	*/
	shortPress = longPress = lastState = currentState = false;
	counter = 0;
	longLimit = 0xFFFF;
}

void Button::scanButton ()
{
	if (!pin.state ()&&!shortPress&&!longPress)
	{
		currentState = !pin.state ();
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
	
	if (counter>shortLimit && counter<longLimit)
	{
		shortPress = 1;
		counter = 0;
	}
	if (counter>longLimit)
	{
		longPress = 1;
		counter = 0;
	}
}

void Button::scanAction ()
{
	if (longPress) 
	{
		longFunction();
		do
			longPress = 0;
		while (!pin.state ());
	}
	if (shortPress)
	{
		shortFunction ();
		do
		shortPress = 0;
		while (!pin.state ());
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

