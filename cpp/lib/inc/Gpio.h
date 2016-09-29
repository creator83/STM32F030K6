#include "stm32f0xx.h"                  // Device header

#ifndef GPIO_H
#define GPIO_H


class Gpio
{
//variables
public:
  enum Port {A , B , C , F=5};
  enum Mode {Input , Output , AltFunc , Analog};
	enum Afmode {AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7};
	enum Omode {PushPull , OpenDrain};
  enum speed {Low = 0 , Medium = 1 , High=3};
  enum PP {NoPP , PullUp , PullDown};

protected:
private:
	static GPIO_TypeDef* GpioBase [6];
  uint8_t prt;
//functions
public:
	Gpio(){}
  Gpio(Port p );
  Gpio(uint8_t p );
  void settingPin (uint8_t pin , Mode m = Output);
	void settingPinPort (Port p);
	void settingAf (uint8_t pin, Afmode a);
	void settingOut (uint8_t pin, Omode o);
  void setPin (uint8_t pin);
  void setPinBit (unsigned int pin);
  void clearPin (unsigned char pin);	
  void setValPort (unsigned int value);	
	void clearPort (unsigned int value);	
  void setOutPort (unsigned int value, speed s = Low );		
  void ChangePinState (unsigned char pin);
  void SetPinState (unsigned char pin , unsigned char state);
  void PuPd (unsigned char pin , PP p);
  bool pinState (unsigned char pin);
};


#endif

