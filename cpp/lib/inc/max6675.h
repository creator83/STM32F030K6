#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "Gpio.h"
#include "Spi.h"
#include "delay.h"

#ifndef MAX6675_H
#define MAX6675_H

	
#define SOFTSPI

class max6675
{
//variables
public:
	
  enum PORT {A , B , C , F=5};

protected:
private:
#ifdef SOFTSPI
  Gpio pin;
#else 
  spi spi1;
#endif	
  union
  {
    uint16_t code16;
    uint8_t code8 [2];
  } byteCode;
  uint8_t sclk, miso, cs;
//functions
public:
  
#ifdef SOFTSPI
  max6675(PORT, int8_t SCLK, int8_t CS, int8_t MISO);
  uint8_t spiread();
#else
  max6675();    
#endif
        
  uint16_t getCode();
  void getChar();
  uint8_t getTemp();
protected:
private:


}; 

#endif //