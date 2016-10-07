#include "stm32f0xx.h"
#include "gpio.h"
#include "delay.h"
#include "tact.h"
#include "pcd8544.h"
#include "systimer.h"
#include "dma.h"
#include "spi.h"


typedef unsigned int* reg;

extern "C"
{
	void DMA1_Channel2_3_IRQHandler(void);
	void DMA1_Channel4_5_IRQHandler(void);
	void SysTick_Handler (void);
}

Tact frq;


	

void SysTick_Handler (void)
{

}


int main()
{
	Spi spi1 (Spi::master, Spi::software);
	Pcd8544 lcd (spi1);
	Pcd8544::sFont sLat, mNum;
	sLat.font = fontLAT;
	sLat.width = 6;
	sLat.shift = 32;
	mNum.width = 16;
	mNum.shift = 48;
	lcd.character (0, 10, 'A', sLat);
	lcd.string (1, 5, 2, "HELLO!!!", sLat);
	delay_ms (3000);
	lcd.string (2, 5 , 2, "12345", mNum);
	while (1)
	{
		lcd.fillScreen ();
		delay_ms (1000);
		lcd.clearScreen ();
		delay_ms (1000);

		/*
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


