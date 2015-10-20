#include "tact.h"

void init_HSI (void)
{
	/* (1) Test if PLL is used as System clock */
	if ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL) 
	{
		/* (2) Select HSI as system clock */
		RCC->CFGR &= ~RCC_CFGR_SW; 
		
		/* (3) Wait for HSI switched */
		while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) ;
	
	}
}

void init_PLL (void)
{
	/* (4) Disable the PLL */
	RCC->CR &= ~RCC_CR_PLLON;
	
	/* (5) Wait until PLLRDY is cleared */
	while((RCC->CR & RCC_CR_PLLRDY) != 0)	;

	/* (6) Set the PLL multiplier to 6 */
	RCC->CFGR = (RCC->CFGR & (~RCC_CFGR_PLLMUL))| (RCC_CFGR_PLLMUL12);
	
	FLASH->ACR |= FLASH_ACR_PRFTBE;
  FLASH->ACR |= FLASH_ACR_LATENCY;
	/* (7) Enable the PLL */
	RCC->CR |= RCC_CR_PLLON; 
	
	/* (8) Wait until PLLRDY is set */
	while((RCC->CR & RCC_CR_PLLRDY) == 0) ;

	/* (9) Select PLL as system clock */
	RCC->CFGR |= (uint32_t) (RCC_CFGR_SW_PLL); 
	
	/* (10) Wait until the PLL is switched on */
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) ;
}
