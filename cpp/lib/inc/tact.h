#include "stm32f0xx.h"                  // Device header

#ifndef TACT_H
#define TACT_H

typedef unsigned int* reg;


class Tact
{
  //variables
public:
  enum srcTact {HSI,HSE, PLL};
	enum ahbDivider {ahbdiv0 = 0, ahbdiv2 = 8, ahbdi4, ahbdiv8, ahbdiv16, ahbdiv64, ahbdiv128, ahbdiv256, ahbdiv512};
	enum apbDivider {apbdiv0 = 0, apbdiv2=4, apbdiv4, apbdiv8, apbdiv16};
private:
  static uint8_t f_cpu;
  uint8_t src;
  //functions
public:
  Tact (uint8_t frq , srcTact s );
  Tact ();
  Tact (srcTact s);
  static uint8_t & get_frq (){return f_cpu;};

  void init_pll (uint8_t i);
  void init_pll ();  
  void init_hse ();
	void setHsi ();
  void setSorce ();  
	void hsiEnable ();
	void hsiDissable ();
	void hseEnable ();
	void hseDissable ();
	void pllEnable ();
	void pllDissable ();
  void setFrq (uint8_t frq);
	void setAPBdiv (apbDivider);
	void setAHBdiv (ahbDivider);
private:
};

 
#endif

