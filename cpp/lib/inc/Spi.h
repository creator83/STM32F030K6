#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"

#ifndef SPI_H
#define SPI_H

typedef unsigned int* reg;


class spi
{
//variables
public:
  enum Division {div2 , div4 , div8 , div16 , div32 , div64 , div128 , div256};
  enum Role {slave , master};
  enum Cpol {neg, pos};
  enum Cpha {falling, rising};

	enum Size {bit4 = 3, bit5, bit6,  bit7,  bit8,  bit9,  bit10, bit11, bit12, bit13, bit14, bit15, bit16};
	enum PORT {A,B};
private:
  Gpio pin;
	static uint8_t pins_d[2][4];
  enum pin_def {CS, SCK , MISO , MOSI};
	uint8_t port_;
//functions
public:
  spi(PORT p, Division div, Cpol cpl = neg, Cpha cph = falling, Role r = master, Size s=bit8);
  void Set_CS ();
  void Clear_CS ();
  void transmit_8 (uint8_t data);
	uint8_t receive_8 ();
  void transmit_16 (uint16_t data);
	uint16_t receive_16 ();
private:
};

#endif

