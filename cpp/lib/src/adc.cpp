#include "adc.h"



Adc::Adc()
{
	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
}

Adc::Adc(Gpio::Port p, uint8_t pin_)
{
	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
	pin.settingPinPort (p);
	pin.settingPin (pin_, Gpio::Analog);
}

void Adc::settingsPin (Gpio::Port p, uint8_t pin_)
{
	pin.settingPinPort (p);
	pin.settingPin (pin_, Gpio::Analog);
}

uint16_t Adc::getValue ()
{
	return ADC1->DR;
}

void Adc::start ()
{
	ADC1->CR |= ADC_CR_ADSTART;
}

void Adc::stop ()
{
}

void Adc::calibrate ()
{
  if ((ADC1->CR & ADC_CR_ADEN) != 0) 
  {
    ADC1->CR &= (uint32_t)(~ADC_CR_ADEN);  
  }
  ADC1->CR |= ADC_CR_ADCAL;
  while ((ADC1->CR & ADC_CR_ADCAL) != 0) 
  {
    /* For robust implementation, add here time-out management */
  }  
}

void Adc::setClock (clockSource s)
{
	if (s == hsi)
	{
		RCC->CR2 |= RCC_CR2_HSI14ON;
		while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0) 
		{
    /* For robust implementation, add here time-out management */
		}  
		ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE;
	}
	else
	{
		ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE;
		ADC1->CFGR2 |= s << 30;		
	}
}

void Adc::enable ()
{
	do 
  {
    /* For robust implementation, add here time-out management */
		ADC1->CR |= ADC_CR_ADEN; /* (1) */
  }
	while ((ADC1->ISR & ADC_ISR_ADRDY) == 0) ;
}

void Adc::disable ()
{
	if ((ADC1->CR & ADC_CR_ADSTART) != 0) 
  {
    ADC1->CR |= ADC_CR_ADSTP; 
  }
  while ((ADC1->CR & ADC_CR_ADSTP) != 0) 
  {
     /* For robust implementation, add here time-out management */
  }
  ADC1->CR |= ADC_CR_ADDIS; 
  while ((ADC1->CR & ADC_CR_ADEN) != 0) 
  {
    /* For robust implementation, add here time-out management */
  }  
}

void Adc::config (mode m,  resolution r)
{
	/* (2) Select the auto off mode */
  /* (5) Wake-up the VREFINT (only for VBAT, Temp sensor and VRefInt) */
  ADC1->CFGR1 |= ADC_CFGR1_AUTOFF; /* (2) */
	ADC1->CFGR1 |= ADC_CFGR1_SCANDIR;
	//Setings resolution
	ADC1->CFGR1 &= ~ADC_CFGR1_RES;
	ADC1->CFGR1 |= r << 3;
  ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; /* (4) */
  ADC->CCR |= ADC_CCR_VREFEN; /* (5) */
	
}

void scmswMode ()
{
	
}

void ccmswMode ()
{
	ADC1->CFGR1 |= ADC_CFGR1_CONT | ADC_CFGR1_SCANDIR; 
}

void Adc::setChannel (channel ch)
{
	ADC1->CHSELR |= ch;
}

void Adc::EocInterrupt (bool state)
{
	ADC1->IER &= ~ ADC_IER_EOCIE;
	ADC1->IER |= state << 2;
}

void Adc::EosmpInterrupt (bool state)
{
	ADC1->IER &= ~ ADC_IER_EOSMPIE;
	ADC1->IER |= state << 1;
}

void Adc::EoseqInterrupt (bool state)
{
	ADC1->IER &= ~ ADC_IER_EOSEQIE;
	ADC1->IER |= state << 3;
}

void Adc::clearEoc ()
{
	ADC1->ISR |= ADC_ISR_EOC ;
}

void Adc::clearEosmp ()
{
	ADC1->ISR |= ADC_ISR_EOSMP ;
}

void Adc::clearEoseq ()
{
	ADC1->ISR |= ADC_ISR_EOSEQ;
}

bool Adc::flagEoc ()
{
	return (ADC1->ISR&ADC_ISR_EOC);
}

bool Adc::flagEosmp ()
{
	return (ADC1->ISR&ADC_ISR_EOSMP);
}

bool Adc::flagEoseq ()
{
	return (ADC1->ISR&ADC_ISR_EOSEQ);
}

