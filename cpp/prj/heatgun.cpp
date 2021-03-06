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
#include "adc.h"
#include "button.h"



Tact frq;
Pid regulator (4.0, 2.2, 1.3, 50);
Gtimer timer14 (Gtimer::Timer14, 60, 100);
Gtimer timer3 (Gtimer::Timer3, 100, 4800);
Qenc encoder (100);
Pwm fun (timer14, Gpio::A, 4, Gpio::AF4, Gtimer::channel1, Pwm::EdgePwm, Pwm::highPulse);

Button buttMenu (Gpio::A, 15);
Spi spi1 (Spi::master, Spi::software);
Pcd8544 lcd (spi1);
Buffer val;
Pcd8544::sFont sLat;


extern "C"
{
	void DMA1_Channel2_3_IRQHandler(void);
	void DMA1_Channel4_5_IRQHandler(void);
	void SysTick_Handler (void);
}



uint16_t valArray [4];
uint8_t menuPosition;

void setFont();

struct tasks
{
	unsigned counter : 6;
	unsigned limit : 6;
	unsigned flag : 1;
}display, button, pid, adc;

struct data
{
	uint8_t strPos;
	uint8_t linePos;
	uint16_t data;
}dataSpeed, dataTemp, dataP, dataI, dataD;


data * dataArray [5] = {&dataSpeed, &dataTemp, &dataP, &dataI, &dataD};

uint16_t adcValue ();

void SysTick_Handler (void)
{
	static uint16_t adcArray [4];
	uint16_t result=0;
	
	fun.setValue (encoder.getValue());
		val.pars (encoder.getValue());
		lcd.stringToBufferDma (1, 45, val.getArray(), sLat);	
	buttMenu.scan();

	
	if (adc.counter>adc.limit) adc.flag = 1;
	if (display.counter > display.limit) display.flag = 1;
	if (pid.counter > pid.limit) pid.flag = 1;
	
	if (adc.flag)
	{
		for (uint8_t i=0;i<4;++i) result += adcArray [i];
		result >>= 2;
		adc.flag = 0;
		adc.counter = 0;
		val.pars (result);
		lcd.stringToBufferDma (1, 45, val.getArray(), sLat);
	}
	else adcArray [adc.counter] = adcValue ();
	if (display.flag) 
	{
		lcd.drawBuffer ();
		display.flag = 0;
		display.counter = 0;
	}
	if (pid.flag) 
	{
		val.pars (regulator.compute (encoder.getValue()));
		pid.flag = 0;
		pid.counter = 0;
	}	
	
	display.counter++;
	pid.counter++;
	adc.counter++;
}

void init_encoder ();
void SetClockForADC();
void CalibrateADC();
void EnableADC();
void ConfigureADC();
void ConfigureADCdma();
void DisableADC();



int main()
{
	

	buttMenu.setShortLimit (10);
	buttMenu.setLongLimit (2000);


	//temperature
	dataTemp.strPos = 15;
	dataTemp.linePos = 1;
	
	//speed
	dataSpeed.strPos = 55;
	dataSpeed.linePos = 1;
	
	//P
	dataP.strPos = 10;
	dataP.linePos = 4;
	dataP.data = regulator.getP();
	
	//I
	dataI.strPos = 40;
	dataI.linePos = 4;	
	dataI.data = regulator.getI();
	//D
	dataD.strPos = 60;
	dataD.linePos = 4;		
	dataD.data = regulator.getD();
	
	adc.limit = 3;
	display.limit = 10;
	
	pid.limit = 9;
	
	Pwm airHeater (timer3, Gpio::B, 0, Gpio::AF1,  Gtimer::channel3, Pwm::EdgePwm, Pwm::highPulse);
	setFont();
	fun.start();
	airHeater.setValue (100);
	airHeater.start();

	lcd.dmaSetting ();
	SetClockForADC();
	CalibrateADC();
	EnableADC();
	ConfigureADC();
	//ConfigureADCdma();
	//===main screen===//
	lcd.stringToBufferDma (0,10, "HEATGUN AIR", sLat);
	lcd.stringToBufferDma (1, 0, "TS:", sLat);
	lcd.stringToBufferDma (1, 40, "SPEED:", sLat);
	lcd.stringToBufferDma (2, 0, "TEMP C:", sLat);
	lcd.stringToBufferDma (3, 0, "ADC:", sLat);
	lcd.stringToBufferDma (4, 0, "P:", sLat);
	lcd.stringToBufferDma (4, 30, "I:", sLat);
	lcd.stringToBufferDma (4, 60, "D:", sLat);
	lcd.stringToBufferDma (5, 0, "PID:", sLat);
	/*lcd.drawBuffer (0, 0, 83);
	lcd.drawBuffer (1, 0, 83);
	lcd.drawBuffer (2, 0, 83);
	lcd.drawBuffer (3, 0, 83);
	lcd.drawBuffer (4, 0, 83);
	NVIC_EnableIRQ(SysTick_IRQn);*/
	Systimer sys (Systimer::ms, 1);

	
	while (1)
	{

	/*	val.pars (adcValue ());
		lcd.stringToBufferDma (3, 45, val.getArray(), sLat);
		
		val.pars (regulator.compute (encoder.getValue()));*/

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
	//DMA1_Channel1->CMAR = (uint32_t)(adcresult); /* (4) */
	DMA1_Channel1->CNDTR = 8; /* (5) */
	DMA1_Channel1->CCR |= DMA_CCR_MINC | DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0
	| DMA_CCR_TEIE | DMA_CCR_CIRC; /* (6) */
	DMA1_Channel1->CCR |= DMA_CCR_EN; /* (7) */
}
