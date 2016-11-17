#include "stm32f0xx.h"                  // Device header
#include "spi.h"
#include "pin.h"


#ifndef SHIFT_REGISTR_H
#define SHIFT_REGISTR_H

class Shift;
typedef void(Shift::*PtrSend)(uint8_t);


class Shift
{
private:
	Pin cs;
	Spi * mod;
	static PtrSend commandSend [2];
	Spi::mode  m;
//functions
public:
	Shift (Spi &, Gpio::Port, uint8_t);
	void setMode ();
	void send (uint8_t data);
private:
	void send_hardware (uint8_t data);
	void send_software (uint8_t data);

};



#endif
