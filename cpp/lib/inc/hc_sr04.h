#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"
#include "intrpt.h"
#include "delay.h"
#include "timer14.h"



#ifndef HC_SR04_H
#define HC_SR04_H

typedef unsigned int* reg;


class hc_sr04
{
//variables
public:
  enum Port {A , B , C , F=5};
	//enum state {Stop, Start};
	
	
private:
	Gpio pin;
	intrpt int1;
	timer14 timer;
	uint8_t trig_;
	uint8_t echo_;
	
//functions
public:
	hc_sr04 (Port p , uint8_t trig, uint8_t echo);
	uint16_t StartStop (uint8_t val);
	void Get_val ();
private:
	void Send_strob();

};


#endif

