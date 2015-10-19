#include "stm32f0xx.h"                  // Device header

#ifndef GPIO_H
#define GPIO_H

typedef unsigned int* reg;


class Gpio
{
//variables
public:
  enum Port {A , B , C , F=5};
  enum mode {Input , Output , AltFunc , Analog};
  enum speed {Low = 0 , Medium = 1 , High=3};
  enum out {PushPull , OpenDrain};
  enum PP {NoPP , PullUp , PullDown};
  enum rgstr {
  Moder = 0x00,
  Otyper = 0x04,
  Ospeedr = 0x08,
  Pupdr = 0x0C,
  Idr = 0x10,
  Odr = 0x14,
  Bsrr = 0x18
};
protected:
private:
  static unsigned int portAdr [6];
  static unsigned int portAdrBit [6];  
//static unsigned int pAdr [3];	
  unsigned char prt;
//functions
public:
  Gpio(Port p );
  Gpio(uint8_t p );
  void setOutPin (unsigned char pin , mode m = Output , speed s = Low , out o = PushPull);	
  void setInPin (unsigned char pin , PP p = NoPP);
  void setPin (unsigned int pin);
  void setPinBit (unsigned int pin);
  void clearPin (unsigned char pin);	
  void setValPort (unsigned int value);	
  void setOutPort (unsigned int value, speed s = Low );		
  void ChangePinState (unsigned char pin);
  void SetPinState (unsigned char pin , unsigned char state);
  void PuPd (unsigned char pin , PP p);
  bool PinState (unsigned char pin);
}; //Gpio


#endif

