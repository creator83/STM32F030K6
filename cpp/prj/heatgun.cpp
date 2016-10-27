#include "stm32f0xx.h"
#include "gpio.h"
#include "delay.h"
#include "tact.h"
#include "pcd8544.h"
#include "systimer.h"
#include "dma.h"
#include "spi.h"
#include "buffer.h"
#include "qenc.h"
#include "pwm.h"
#include "gtimer.h"
#include "pid.h"


extern "C"
{
	void DMA1_Channel2_3_IRQHandler(void);
	void DMA1_Channel4_5_IRQHandler(void);
	void SysTick_Handler (void);
}

Tact frq;
Pid regulator (4.0, 2.2, 1.3, 40);
Gtimer timer14 (Gtimer::Timer14, 60, 100);
Gtimer timer3 (Gtimer::Timer3, 100, 4800);
Qenc encoder (100);
Pwm fun (timer14, Gpio::A, 4, Gpio::AF4, Gtimer::channel1, Pwm::EdgePwm, Pwm::highPulse);


Spi spi1 (Spi::master, Spi::software);
Pcd8544 lcd (spi1);
Buffer val (5);
Pcd8544::sFont sLat;


void setFont();

struct encdr
{
	uint8_t state;
	uint16_t count;
}encod;
uint16_t N = 62;

uint16_t adcresult [8];
uint16_t result;

void SysTick_Handler (void)
{
	
	//write to buffer encoder value
	
}

void init_encoder ();
void SetClockForADC();
void CalibrateADC();
void EnableADC();
void ConfigureADC();
void ConfigureADCdma();
void DisableADC();
uint16_t adcValue ();

int main()
{
	Pwm airHeater (timer3, Gpio::B, 0, Gpio::AF1,  Gtimer::channel3, Pwm::EdgePwm, Pwm::highPulse);
	//init_encoder ();
	setFont();
	fun.start();
	airHeater.setValue (3000);
	airHeater.start();

	lcd.dmaSetting ();
	SetClockForADC();
	CalibrateADC();
	EnableADC();
	ConfigureADC();
	//ConfigureADCdma();
	//===main screen===//
	lcd.stringToBufferDma (0,10, "HEATGUN AIR", sLat);
	lcd.stringToBufferDma (1, 0, "TEMP S:", sLat);
	lcd.stringToBufferDma (2, 0, "TEMP C:", sLat);
	lcd.stringToBufferDma (3, 0, "ADC:", sLat);
	lcd.stringToBufferDma (4, 0, "PID:", sLat);
	lcd.drawBuffer ();
	/*lcd.drawBuffer (0, 0, 83);
	lcd.drawBuffer (1, 0, 83);
	lcd.drawBuffer (2, 0, 83);
	lcd.drawBuffer (3, 0, 83);
	lcd.drawBuffer (4, 0, 83);*/

	
	while (1)
	{
		fun.setValue (encoder.getValue());
		val.pars (encoder.getValue());
		lcd.stringToBufferDma (1, 45, val.getArray(), sLat);
		lcd.drawBuffer ();
	/*	val.pars (adcValue ());
		lcd.stringToBufferDma (3, 45, val.getArray(), sLat);
		
		val.pars (regulator.compute (encoder.getValue()));*/
		delay_ms (100);
	}
}

void setFont()
{
	sLat.font = fontLAT;
	sLat.width = 6;
	sLat.shift = 32;
}



void SetClockForADC()
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 
  RCC->CR2 |= RCC_CR2_HSI14ON; 
  while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0) 
  {
    /* For robust implementation, add here time-out management */
  }  
}

void  CalibrateADC()
{	
  /* (1) Ensure that ADEN = 0 */
  /* (2) Clear ADEN */ 
  /* (3) Launch the calibration by setting ADCAL */
  /* (4) Wait until ADCAL=0 */
  if ((ADC1->CR & ADC_CR_ADEN) != 0) /* (1) */
  {
    ADC1->CR &= (uint32_t)(~ADC_CR_ADEN);  /* (2) */  
  }
  ADC1->CR |= ADC_CR_ADCAL; /* (3) */
  while ((ADC1->CR & ADC_CR_ADCAL) != 0) /* (4) */
  {
    /* For robust implementation, add here time-out management */
  }  
}

void EnableADC()
{
  /* (1) Enable the ADC */
  /* (2) Wait until ADC ready */
  do 
  {
    /* For robust implementation, add here time-out management */
		ADC1->CR |= ADC_CR_ADEN; /* (1) */
  }while ((ADC1->ISR & ADC_ISR_ADRDY) == 0) /* (2) */;
}
void DisableADC()
{
  /* (1) Ensure that no conversion on going */
  /* (2) Stop any ongoing conversion */
  /* (3) Wait until ADSTP is reset by hardware i.e. conversion is stopped */
  /* (4) Disable the ADC */
  /* (5) Wait until the ADC is fully disabled */
  if ((ADC1->CR & ADC_CR_ADSTART) != 0) /* (1) */
  {
    ADC1->CR |= ADC_CR_ADSTP; /* (2) */
  }
  while ((ADC1->CR & ADC_CR_ADSTP) != 0) /* (3) */
  {
     /* For robust implementation, add here time-out management */
  }
  ADC1->CR |= ADC_CR_ADDIS; /* (4) */
  while ((ADC1->CR & ADC_CR_ADEN) != 0) /* (5) */
  {
    /* For robust implementation, add here time-out management */
  }  
}

uint16_t adcValue ()
{
		ADC1->CR |= ADC_CR_ADSTART; /* start the ADC conversion */
    while ((ADC1->ISR & ADC_ISR_EOC) == 0); 
		return ADC1->DR;
}

void ConfigureADC()
{
  /* (1) Select HSI14 by writing 00 in CKMODE (reset value) */ 
  /* (2) Select the auto off mode */
  /* (3) Select CHSEL17 for VRefInt */
  /* (4) Select a sampling mode of 111 i.e. 239.5 ADC clk to be greater than 17.1us */
  /* (5) Wake-up the VREFINT (only for VBAT, Temp sensor and VRefInt) */
  //ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE; /* (1) */   
  ADC1->CFGR1 |= ADC_CFGR1_AUTOFF; /* (2) */
  ADC1->CHSELR = ADC_CHSELR_CHSEL0; /* (3) */
  ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; /* (4) */
  ADC->CCR |= ADC_CCR_VREFEN; /* (5) */
}

void ConfigureADCdma()
{
	/* (1) Enable the peripheral clock on DMA */
	/* (2) Enable DMA transfer on ADC and circular mode */
	/* (3) Configure the peripheral data register address */
	/* (4) Configure the memory address */
	/* (5) Configure the number of DMA tranfer to be performs
	on DMA channel 1 */
	/* (6) Configure increment, size, interrupts and circular mode */
	/* (7) Enable DMA Channel 1 */
	RCC->AHBENR |= RCC_AHBENR_DMA1EN; /* (1) */
	ADC1->CHSELR = ADC_CHSELR_CHSEL1;
	ADC1->CFGR1 |= ADC_CFGR1_CONT;
	ADC1->CFGR1 |= ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG; /* (2) */
	DMA1_Channel1->CPAR = (uint32_t) (&(ADC1->DR)); /* (3) */
	DMA1_Channel1->CMAR = (uint32_t)(adcresult); /* (4) */
	DMA1_Channel1->CNDTR = 8; /* (5) */
	DMA1_Channel1->CCR |= DMA_CCR_MINC | DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0
	| DMA_CCR_TEIE | DMA_CCR_CIRC; /* (6) */
	DMA1_Channel1->CCR |= DMA_CCR_EN; /* (7) */
}
