#include "stm32f0xx.h"                  // Device header
#include "spi.h"
#include "gpio.h"

namespace ShiftDef
{
//===Defenitions===//
//CS
const Gpio::Port CsPort = Gpio::A;
const uint8_t CsPin = 4;

//SCK
const Gpio::Port SckPort = Gpio::A;
const uint8_t SckPin = 5;

//MOSI
const Gpio::Port MosiPort = Gpio::A;
const uint8_t MosiPin = 7;
}

#ifndef SHIFT_REGISTR_H
#define SHIFT_REGISTR_H

class Shift;
typedef void(Shift::*PtrSend)(uint8_t);


class Shift
{
private:
	Gpio CS, SCK, MOSI;
	Spi * mod;
	static PtrSend commandSend [2];
	Spi::mode  m;
//functions
public:
	Shift (Spi &);
	void setMode ();
	void send (uint8_t data);
private:
	void send_hardware (uint8_t data);
	void send_software (uint8_t data);

};



#endif
