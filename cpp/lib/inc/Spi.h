#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"

#define SPI1_DR_8bit          (*(__IO uint8_t *)((uint32_t)&(SPI1->DR))) 


#ifndef SPI_H
#define SPI_H

class spi;

typedef uint16_t(spi::*PotMemFn)() ;

class spi
{
//variables
public:
  enum Division {div2 , div4 , div8 , div16 , div32 , div64 , div128 , div256};
  enum Role {slave , master};
  enum Cpol {neg, pos};
  enum Cpha {first, second};
	static uint8_t pins_d[2][4];
	enum Size {bit8, bit16};
	enum PORT {A,B};
	
	enum pin_def {CS, SCK , MISO , MOSI};
	uint8_t port_;
	uint8_t size_;
private:
  Gpio pin;
	static PotMemFn ptr_receive[2];

//functions
public:
  spi(PORT p, Division div, Cpol cpl = neg, Cpha cph = first, Role r = master, Size s=bit8);
  void Set_CS ();
  void Clear_CS ();
  void transmit_8 (uint8_t data);
	uint16_t receive_8 ();
  void transmit_16 (uint16_t data);
	uint16_t receive_16 ();
	uint16_t receive ();
private:
};

#endif

