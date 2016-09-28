#include "stm32f0xx.h"                  // Device header

#ifndef GPIO_H
#define GPIO_H


class Gpio
{
//variables
public:
  enum Port {A , B , C , F=5};
  enum mode {Input , Output , AltFunc , Analog};
  enum speed {Low = 0 , Medium = 1 , High=3};
  enum out {PushPull , OpenDrain};
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
  void settingPin (uint8_t pin , mode m = Output);	
  void setInPin (unsigned char pin , PP p = NoPP);
  void setPin (unsigned int pin);
  void setPinBit (unsigned int pin);
  void clearPin (unsigned char pin);	
  void setValPort (unsigned int value);	
	void clearPort (unsigned int value);	
  void setOutPort (unsigned int value, speed s = Low );		
  void ChangePinState (unsigned char pin);
  void SetPinState (unsigned char pin , unsigned char state);
  void PuPd (unsigned char pin , PP p);
  bool PinState (unsigned char pin);
};


#endif

