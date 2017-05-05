#include "device.h"
#include "gpio.h"

#ifndef PIN_H
#define PIN_H


class Pin : protected Gpio
{
  //variables
public:

private:
  private:
  uint8_t pin_;
  //functions
public:
 Pin(Port prt, uint8_t p_);
	Pin(Port prt, uint8_t p_, Mode);
	Pin(Port prt, uint8_t p_, Afmode);
	Pin(Port prt, uint8_t p_, Omode);
	Pin(Port prt, uint8_t p_, PP);

	void setInputMode (PP);
	void setOutputMode (Omode = Omode::PushPull);
  
	void set ();
	void clear ();
	void togle ();
	bool state ();
	GPIO_TypeDef * getPort ();

	uint8_t & getPin ();
};




#endif
