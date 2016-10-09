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

typedef unsigned int* reg;

extern "C"
{
	void DMA1_Channel2_3_IRQHandler(void);
	void DMA1_Channel4_5_IRQHandler(void);
	void SysTick_Handler (void);
}

Tact frq;
Gpio A (Gpio::A);
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

int main()
{
	Gtimer timer14 (Gtimer::Timer14, 33);
	timer14.setArr (100);
	init_encoder ();
	Pwm led_pwm (timer14, Gpio::B, 1, Gpio::AF0, Gtimer::channel1, Pwm::EdgePwm, Pwm::highPulse);
	led_pwm.start();
	Spi spi1 (Spi::master, Spi::software);
	Pcd8544 lcd (spi1);
	Buffer val (4);
	Pcd8544::sFont sLat;
	sLat.font = fontLAT;
	sLat.width = 6;
	sLat.shift = 32;
	lcd.setLinePosition (0, 10);
	lcd.byte (0xFF);
	
	lcd.character (0, 10, 'A', sLat);
	lcd.string (1, 5, "HELLO!!!", sLat);
	lcd.string (2, 5 , "12345", sLat);
	lcd.string (3, 0 , "PWM", sLat);
	
	
	while (1)
	{
		led_pwm.setValue (TIM3->CNT>>2);
		val.pars (TIM3->CNT>>2);
		lcd.string (3, 25 , val.getArray(), sLat);
		delay_ms (1);
			
		/*;
		val.pars (N)
	
		for (uint8_t i=0;i<10;++i)
		{
			number_[0] = i;
			delay_ms (300);
		}

		for (uint8_t i=0;i<2;++i)
		{
			lcd.draw_picture (arr[i], length);
			delay_ms (500);
		}*/
	
	}
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
