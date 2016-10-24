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
Gpio A (Gpio::A);
Pid regulator (4.0, 2.2, 1.3, 40);


struct encdr
{
	uint8_t state;
	uint16_t count;
}encod;
uint16_t N = 62;

const uint8_t pha = 8;
const uint8_t phb = 9;

void scan_enc ();
	

void SysTick_Handler (void)
{

}

void init_encoder ();
void SetClockForADC();
void CalibrateADC();
void EnableADC();
void ConfigureADC();
void DisableADC();

int main()
{
	Gtimer timer14 (Gtimer::Timer14, 48000);
	timer14.setArr (2000);
	//init_encoder ();
	Qenc encoder (100);
	Pwm led_pwm (timer14, Gpio::B, 1, Gpio::AF0, Gtimer::channel1, Pwm::EdgePwm, Pwm::highPulse);
	led_pwm.setValue (100);
	led_pwm.start();
	Spi spi1 (Spi::master, Spi::software);
	Pcd8544 lcd (spi1);
	Buffer val (5);
	SetClockForADC();
	CalibrateADC();
	EnableADC();
	ConfigureADC();
	Pcd8544::sFont sLat;
	sLat.font = fontLAT;
	sLat.width = 6;
	sLat.shift = 32;
	lcd.character (0, 10, 'A', sLat);
	lcd.string (1, 5, "HELLO!!!", sLat);
	lcd.string (4, 5 , "ADC", sLat);
	
	lcd.dmaSetting ();
	lcd.stringToBuffer (0,0, "BUFF WITHOUT DMA", sLat);
	lcd.stringToBufferDma (1, 0, "BUFF WITH DMA", sLat);
	lcd.stringToBufferDma (2, 0, "TEMP SET:", sLat);
	lcd.stringToBufferDma (3, 0, "ADC:", sLat);
	lcd.stringToBufferDma (4, 0, "PID:", sLat);
	lcd.drawBufferDma ();
	
	while (1)
	{
		
		val.pars (encoder.getValue());
		//lcd.string (2, 54 , val.getArray(), sLat);
		lcd.stringToBufferDma (2, 54, val.getArray(), sLat);
		lcd.drawBufferDma (2, 54, 83);
		ADC1->CR |= ADC_CR_ADSTART; /* start the ADC conversion */
    while ((ADC1->ISR & ADC_ISR_EOC) == 0); 
		val.pars (ADC1->DR);
		lcd.string (3, 25 , val.getArray(), sLat);
		ADC1->ISR |= ADC_ISR_EOC;
		val.pars (regulator.compute (encoder.getValue()));
		lcd.string (4, 25 , val.getArray(), sLat);
		delay_ms (1);
	}
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

void ConfigureADC()
{
  /* (1) Select HSI14 by writing 00 in CKMODE (reset value) */ 
  /* (2) Select the auto off mode */
  /* (3) Select CHSEL17 for VRefInt */
  /* (4) Select a sampling mode of 111 i.e. 239.5 ADC clk to be greater than 17.1us */
  /* (5) Wake-up the VREFINT (only for VBAT, Temp sensor and VRefInt) */
  //ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE; /* (1) */   
  ADC1->CFGR1 |= ADC_CFGR1_AUTOFF; /* (2) */
  ADC1->CHSELR = ADC_CHSELR_CHSEL1; /* (3) */
  ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; /* (4) */
  ADC->CCR |= ADC_CCR_VREFEN; /* (5) */
}

void init_encoder ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 
	GPIOB->MODER &=~( GPIO_MODER_MODER4| GPIO_MODER_MODER5);
	GPIOB->MODER |= GPIO_MODER_MODER4_1| GPIO_MODER_MODER5_1;
	GPIOB->PUPDR = 0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR4_0|GPIO_PUPDR_PUPDR5_0;
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFR4|GPIO_AFRL_AFR5); 
	GPIOB->AFR[0] |= 1 << 16| 1 << 20;
	TIM3->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
	TIM3->CCMR1 |= TIM_CCMR1_IC1F_1| TIM_CCMR1_IC2F_1 ;
  TIM3->CCER &= (uint16_t)(~(TIM_CCER_CC1P | TIM_CCER_CC2P));
	TIM3->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
  TIM3->CR1 |= TIM_CR1_CEN;
  /*RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; 
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
  GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9))
               | (GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1); 
	GPIOA->PUPDR = 0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR8_0|GPIO_PUPDR_PUPDR9_0;
	
  GPIOA->AFR[1] |= 0x2 | (0x2 << ((9-8)*4)); 
  
  TIM1->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
  TIM1->CCER &= (uint16_t)(~(TIM_CCER_CC1P | TIM_CCER_CC2P));
	TIM1->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
  TIM1->CR1 |= TIM_CR1_CEN; */
	
	
}
	/*
void init_dma_spi_tx ()
{
	RCC->AHBENR |= RCC_AHBENR_DMAEN;
	SPI1->CR2 |= SPI_CR2_TXDMAEN;
	DMA1_Channel3->CPAR = (uint32_t) (&(SPI1->DR));
	DMA1_Channel3->CMAR = (uint32_t) (arr [2]);
	DMA1_Channel3->CNDTR = length;
	DMA1_Channel3->CCR &= ~ (DMA_CCR_MSIZE|DMA_CCR_PSIZE);
	DMA1_Channel3->CCR |= DMA_CCR_MINC|DMA_CCR_TCIE |DMA_CCR_DIR;
	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

}*/
/*
void init_dma_mem ()
{
	RCC->AHBENR |= RCC_AHBENR_DMAEN;
	DMA1_Channel5->CPAR = (uint32_t) (pic1);
	DMA1_Channel5->CMAR = (uint32_t) (pic);

	
	//DMA1_Channel5->CNDTR = length;
	DMA1_Channel5->CCR &= ~ (DMA_CCR_MSIZE|DMA_CCR_PSIZE);
	DMA1_Channel5->CCR |= DMA_CCR_MINC|DMA_CCR_TCIE |DMA_CCR_DIR|DMA_CCR_PINC	| DMA_CCR_MEM2MEM; 
	NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);	
}

void pic_shift (uint8_t sh)
{
	for (uint16_t i=0;i< length;++i)buffer[i] = 0;
	for (uint8_t i=sh;i<84;++i)
	{
		buffer[i] = *pic2;
	}
}
*/


void scan_enc ()
{
  uint8_t new_;
  new_ = (1 << A.pinState(pha))|A.pinState(phb);
  switch (encod.state)
  {
    case 2:
    {
      if (new_ == 3) encod.count++;
      if (new_ == 0) encod.count--;
      break;
    }
    case 0:
    {
      if (new_ == 2) encod.count++;
      if (new_ == 1) encod.count--;
      break;
    }
    case 1:
    {
      if (new_ == 0) encod.count++;
      if (new_ == 3) encod.count--;
      break;
    }		
    case 3:
    {
      if (new_ == 1) encod.count++;
      if (new_ == 2) encod.count--;
      break;
    }				
  }
    encod.state = new_;
    N = encod.count>>1;
}
