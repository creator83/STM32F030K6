#include "device.h"                  // Device header

#ifndef TACT_H
#define TACT_H

typedef unsigned int* reg;


class Tact
{
  //variables
public:

  enum class srcTact {HSI,HSE, PLL};
	enum class ahbDivider {div0 = 0, div2 = 8, div4, div8, div16, div64, div128, div256, div512};
	enum class apbDivider : uint8_t {div0 = 0, div2=4, div4, div8, div16};

private:
  static uint16_t f_cpu;
  uint8_t src;
  //functions
public:
  Tact (uint8_t frq , srcTact s );
  Tact ();
  Tact (srcTact s);
  static uint16_t & get_frq (){return f_cpu;};

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

