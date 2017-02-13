#include "tact.h"

uint16_t Tact::f_cpu;

Tact::Tact ()
{
  f_cpu = 48000;
  setHsi ();
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE|RCC_CFGR_PLLMUL);
    
  RCC->CFGR |= RCC_CFGR_PLLMULL12;
  FLASH->ACR |= FLASH_ACR_PRFTBE;
  FLASH->ACR |= FLASH_ACR_LATENCY;
  
  RCC->CR |= RCC_CR_PLLON;
  
  while(!((RCC->CR)&RCC_CR_PLLRDY));
  RCC->CFGR &= RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while (!((RCC->CFGR)&RCC_CFGR_SWS_PLL ));
  
}

Tact::Tact (srcTact s)
{
  src = static_cast <uint8_t> (s);
  //f_cpu = 48;
  if (src) init_hse ();
  else 
	{
		hsiEnable ();
		setHsi ();
	}
  
  //init_pll();
}

Tact::Tact (uint8_t frq, srcTact s )
{
  setFrq(frq);
  src = static_cast <uint8_t> (s);
  
  if (src) init_hse();
  else setHsi ();

  init_pll(f_cpu);
}

void Tact::init_hse ()
{
  RCC->CR |= RCC_CR_HSEON;
  while (!((RCC->CR)&RCC_CR_HSERDY));
  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_HSE;
}

void Tact::setHsi ()
{
		RCC->CFGR &= ~RCC_CFGR_SW; 
		while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) ;	
}

void Tact::hsiEnable ()
{
	RCC->CR |= RCC_CR_HSION;
	while (!RCC->CR&RCC_CR_HSIRDY);
}

void Tact::hsiDissable ()
{
	RCC->CR &= ~RCC_CR_HSION;
}

void Tact::hseEnable ()
{
	RCC->CR |= RCC_CR_HSEON;
	while (!RCC->CR&RCC_CR_HSERDY);
}

void Tact::hseDissable ()
{
	RCC->CR &= ~ RCC_CR_HSEON;
}

void Tact::pllEnable ()
{
	RCC->CR |= RCC_CR_PLLON;
	while (!RCC->CR&RCC_CR_PLLRDY);
}
void Tact::pllDissable ()
{
	RCC->CR &= ~ RCC_CR_PLLON;
}

void Tact::setFrq (uint8_t frq)
{
  if (frq>48) f_cpu = 48;
  else if (frq<4) f_cpu = 4;
  else f_cpu = (frq/4)*4;
  
}

//Init PLL
void Tact::init_pll ()
{
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE|RCC_CFGR_PLLMUL);  
  
  if (src)
  { 
    RCC->CFGR |= (src << 16) & RCC_CFGR_PLLSRC_HSE_PREDIV;
    RCC->CFGR2 |= RCC_CFGR2_PREDIV1_DIV2 ; 
  }  
  RCC->CFGR |= RCC_CFGR_PLLMULL12;
  FLASH->ACR |= FLASH_ACR_PRFTBE;
  FLASH->ACR |= FLASH_ACR_LATENCY;   
    
  RCC->CR |= RCC_CR_PLLON;
  
  while(!((RCC->CR)&RCC_CR_PLLRDY));
  RCC->CFGR &= RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while (!((RCC->CFGR)&RCC_CFGR_SWS_PLL ));    
  
}    

void Tact::init_pll (uint8_t i)
{
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE|RCC_CFGR_PLLMUL);

  if (src)
  { 
    RCC->CFGR |= (src << 16) & RCC_CFGR_PLLSRC_HSE_PREDIV;
    RCC->CFGR2 |= RCC_CFGR2_PREDIV1_DIV2 ; 
  }
  
  switch (i)
  {
  case 4:
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;      
  break;
  case 8:
    RCC->CFGR |= RCC_CFGR_PLLMULL2;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;   
  break;
  case 12:
    RCC->CFGR |= RCC_CFGR_PLLMULL3;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;    
  break;   
  case 16:
    RCC->CFGR |= RCC_CFGR_PLLMULL4;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;    
  break;  
  case 20:
    RCC->CFGR |= RCC_CFGR_PLLMULL5;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;    
  break;   
  case 24:
    RCC->CFGR |= RCC_CFGR_PLLMULL6;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;    
  break;     
  case 28:
    RCC->CFGR |= RCC_CFGR_PLLMULL7;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR |= FLASH_ACR_LATENCY;   
  break;    
  case 32:
    RCC->CFGR |= RCC_CFGR_PLLMULL8;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR |= FLASH_ACR_LATENCY;   
  break;      
  case 36:
    RCC->CFGR |= RCC_CFGR_PLLMULL9;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR |= FLASH_ACR_LATENCY;   
  break;      
  case 40:
    RCC->CFGR |= RCC_CFGR_PLLMULL10;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR |= FLASH_ACR_LATENCY;   
  break;  
  case 44:
    RCC->CFGR |= RCC_CFGR_PLLMULL11;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR |= FLASH_ACR_LATENCY;   
  break;  
  case 48:
    RCC->CFGR |= RCC_CFGR_PLLMULL12;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR |= FLASH_ACR_LATENCY;   
  break;  
  }
  
  RCC->CR |= RCC_CR_PLLON;
  
  while(!((RCC->CR)&RCC_CR_PLLRDY));
  RCC->CFGR &= RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while (!((RCC->CFGR)&RCC_CFGR_SWS_PLL ));
}

void Tact::setAPBdiv (apbDivider div)
{
	RCC->CFGR &= ~RCC_CFGR_PPRE;
	RCC->CFGR |= static_cast <uint8_t> (div) << 8;
}

void Tact::setAHBdiv (ahbDivider div)
{
	RCC->CFGR &= ~RCC_CFGR_HPRE;
	RCC->CFGR |= static_cast <uint8_t> (div) << 4;
}

