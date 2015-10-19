#include "tact.h"

uint8_t tact::f_cpu;

tact::tact ()
{
  f_cpu = 48;
  init_hsi ();
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

tact::tact (src_tact s)
{
  src = s;
  f_cpu = 48;
  if (s) init_hse();
  else init_hsi();
  
  init_pll();
}

tact::tact (uint8_t frq, src_tact s )
{
  Set_frq(frq);
  src = s;
  
  if (s) init_hse();
  else init_hsi();

  init_pll(f_cpu);
}

void tact::init_hse ()
{
  RCC->CR |= RCC_CR_HSEON;
  while (!((RCC->CR)&RCC_CR_HSERDY));
  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_HSE;
}

void tact::init_hsi ()
{
  RCC->CR |= RCC_CR_HSION;
  while (!((RCC->CR)&RCC_CR_HSIRDY));
  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_HSI;
}
void tact::Set_frq (uint8_t frq)
{
  if (frq>48) f_cpu = 48;
  else if (frq<4) f_cpu = 4;
  else f_cpu = (frq/4)*4;
  
}

//настройка на 48МГц
void tact::init_pll ()
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

void tact::init_pll (uint8_t i)
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

