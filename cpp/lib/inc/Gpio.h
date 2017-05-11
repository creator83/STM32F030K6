#include "device.h"                  // Device header

#ifndef GPIO_H
#define GPIO_H


class Gpio
{
//variables
public:
  enum class Port {A , B , C , F=5};
  enum class Mode {Input , Output , AltFunc , Analog};
	enum class Afmode {AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7};
	enum class Omode {PushPull , OpenDrain};
  enum class speed {Low = 0 , Medium = 1 , High=3};
  enum class PP {NoPP , PullUp , PullDown};
	

protected:
	static GPIO_TypeDef* GpioBase [6];
  uint8_t prt;
private:
	
//functions
public:
	Gpio(){}
  Gpio(Port p );
  Gpio(uint8_t p );
  void setValPort (unsigned int value);	
	void clearPort (unsigned int value);	
	void setOutPort (unsigned int value, speed s = speed::Low );		
  void PuPd (unsigned char pin , PP p);

};


#endif

