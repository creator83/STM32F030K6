
#include "Gpio.h"

#ifndef __SEG_LED_H__
#define __SEG_LED_H__
//#define Shift


class seg_led
{
//variables
public:
	static unsigned char time;
	static char digit [11];
	static char digitDp [11];
	unsigned char hun , dec, ones, decimal;
	uint8_t numb[4];
	static uint8_t d[4];
	
	

private:
Gpio seg;
Gpio dig;
enum N_dig {fourth, third, second, first};
//enum N_dig {first, second, third, fourth};
enum DIG { ons, decimals, hundret, tous};
Timer0 timer;
//functions
public:
	seg_led();
	void Show_digit (float num);
	void Show_digit (uint8_t num , uint8_t i);	
	void Show_digit1 (float num);
	//void Calc_digit (unsigned int n);
	void Calc_digit (float n);
	void Calc_digit (uint8_t n);
	unsigned int div10 (unsigned int);

}; //seg_led

ISR (TIMER0_OVF_vect);

#endif //__SEG_LED_H__
