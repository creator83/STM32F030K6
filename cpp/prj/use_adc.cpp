#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "Spi.h"
#include "nrf24l01.h"
#include "pcd8544.h"
#include "systimer.h"
#include "dma.h"


typedef unsigned int* reg;

extern "C"
{
	void DMA1_Channel2_3_IRQHandler(void);
	void DMA1_Channel4_5_IRQHandler(void);
	void SysTick_Handler (void);
}

tact frq;
pcd8544 lcd;
//Gpio Adc (Gpio::A);

const uint8_t adc_pin = 0;

void init_adc ();
void buff_arr (uint16_t mes, uint8_t * arr);
uint16_t single_conv ();

void SysTick_Handler (void)
{
	lcd.draw_buffer ();
}

uint8_t buff [4];

int main()
{
	uint16_t result=0;
	lcd.clear_buffer ();
	init_adc ();
	systimer sys(systimer::ms, 300);
	lcd.point_buffer (21, 2, 3);
	
	while (1)
	{
		result = (single_conv ()*3.3*100)/4095;
		buff_arr (result, buff);
		lcd.big_number_buffer (5,0,buff [0]);
		lcd.string_number_buffer (26,0,&buff[1],2);
	}
}



void init_adc ()
{
	//Settings gpio
//	Adc.setOutPin (adc_pin, Gpio::Analog);


	  // Configure ADC pin, PA0-PA4 analog
             RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
             GPIOA->MODER |= GPIO_MODER_MODER0;
		//===Adc clock seection===//
	// (1) Enable the peripheral clock of the ADC 
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	// (2) Start HSI14 RC oscillator 
	RCC->CR2 |= RCC_CR2_HSI14ON; 
	//RCC->CFGR |= RCC_CFGR_PPRE_2; 
	
	// (3) Wait HSI14 is ready 
	while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0) // (3)
	{
	// For robust implementation, add here time-out management 
	}	
	
		//=== Adc calibration===//
	// (1) Ensure that ADEN = 0 
	if ((ADC1->CR & ADC_CR_ADEN) != 0) 
	{
		// (2) Clear ADEN 
		ADC1->CR &= (uint32_t)(~ADC_CR_ADEN); 
	}
	
	// (3) Launch the calibration by setting ADCAL 
	ADC1->CR |= ADC_CR_ADCAL;
	
	// (4) Wait until ADCAL=0 
	while ((ADC1->CR & ADC_CR_ADCAL) != 0) 
	{
	// For robust implementation, add here time-out management 
	}
	
	//===Adc enable===//
	// (1) Enable the ADC 
	ADC1->CR |= ADC_CR_ADEN;
	
	// (2) Wait until ADC ready 
	while ((ADC1->ISR & ADC_ISR_ADRDY) == 0)
	{
	// For robust implementation, add here time-out management 
	}	
	
	

		
	// (2) Select CHSEL0, CHSEL9, CHSEL10 andCHSEL17 for VRefInt 
	ADC1->CHSELR = ADC_CHSELR_CHSEL0 
	//| ADC_CHSELR_CHSEL9
	//| ADC_CHSELR_CHSEL10 | ADC_CHSELR_CHSEL17
	;
	
	// (3) Select a sampling mode of 111 i.e. 239.5 ADC clk to be greater	than 17.1us 
	ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; 
	
	// (4) Wake-up the VREFINT (only for VBAT, Temp sensor and VRefInt) 
	//ADC->CCR |= ADC_CCR_VREFEN;

	/*
	
	 RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 
	 RCC->CFGR |= RCC_CFGR_PPRE_2;
      
      
        // (1) Ensure that ADEN = 0 
      // (2) Clear ADEN 
      // (3) Launch the calibration by setting ADCAL 
      // (4) Wait until ADCAL=0 
       if ((ADC1->CR & ADC_CR_ADEN) != 0) // (1) 
         {
               ADC1->CR &= (uint32_t)(~ADC_CR_ADEN);  // (2) 
            }
            ADC1->CR |= ADC_CR_ADCAL; // (3) 
            while ((ADC1->CR & ADC_CR_ADCAL) != 0) // (4) 
            {
               // For robust implementation, add here time-out management 
            }
            
             // Configure ADC pin, PA0-PA4 analog
             RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
             GPIOA->MODER |= GPIO_MODER_MODER0;
                  
            
          do
            {
               // For robust implementation, add here time-out management 
               ADC1->CR |= ADC_CR_ADEN; // (1)
            }while ((ADC1->ISR & ADC_ISR_ADRDY) == 0); // (2) ;

            
         // (1) Select PCLK/2 by writing 01 in CKMODE 
         // (2) Select the continuous mode 
         // (3) Select CHSEL1, CHSEL9, CHSEL10 and CHSEL17 
         // (4) Select a sampling mode of 111 i.e. 239.5 ADC clk to be greater than 17.1us 
         // (5) Enable interrupts on overrrun 
         // (6) Wake-up the VREFINT (only for VBAT, Temp sensor and VRefInt) 
         ADC1->CFGR2 |= ADC_CFGR2_CKMODE_0; // (1) 
         ADC1->CFGR1 |= ADC_CFGR1_CONT; // (2)
         ADC1->CHSELR = ADC_CHSELR_CHSEL0;
         
         ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; // (4) 
			*/	 

}

void buff_arr (uint16_t mes, uint8_t * arr)
{
	char hundr, dec, ones = 0;
	uint16_t temp = mes;
	for (hundr=0;temp>=100;++hundr)temp -=100;
	
	for (dec=0;temp>=10;++dec)temp -=10;

	for (ones=0;temp>=1;++ones)temp--;
		arr [0] = hundr;
		arr [1] = dec;
		arr [2] = ones;
}

uint16_t single_conv ()
{
		uint16_t Adc_result=0;
		/* Performs the AD conversion */
	while (!ADC1->ISR & ADC_ISR_ADRDY);
		ADC1->CR |= 1 << 2
	//ADC_CR_ADSTART
	; /* Start the ADC conversion */
			while ((ADC1->ISR & ADC_ISR_EOC) == 0) /* Wait end of conversion */
			{
				/* For robust implementation, add here time-out management */
			}
			Adc_result = ADC1->DR; /* Store the ADC conversion result */

		//ADC1->CFGR1 ^= ADC_CFGR1_SCANDIR;
	ADC1->ISR |= ADC_ISR_EOC;
	ADC1->ISR |= ADC_ISR_EOSMP;
	ADC1->ISR |= ADC_ISR_EOSEQ;		
	return Adc_result;
}

