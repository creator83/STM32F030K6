#include "stm32f0xx.h"                  // Device header
#include "spi.h"
#include "delay.h"

namespace Max6675Def
{
//===Defenitions===//
//CS
const Gpio::Port CsPort = Gpio::A;
const uint8_t CsPin = 4;

//SCK
const Gpio::Port SckPort = Gpio::A;
const uint8_t SckPin = 5;

//MISO
const Gpio::Port MisoPort = Gpio::A;
const uint8_t MisoPin = 6;
}

#ifndef MAX6675_H
#define MAX6675_H


class Max6675;
typedef bool(Max6675::*Ptrdata)(uint8_t);

class Max6675
{
//variables
public:

private:
	Gpio CS, SCK, MOSI;
	Spi * mod;
	static Ptrdata receiveF [2];
	Spi::mode  m;
	uint16_t temp;
//functions
public:
	Max6675 (Spi &);
	void setMode ();
	bool readCelsius();
private:
	bool readCelsius_hardware();
	bool readCelsius_software();
};
#endif
