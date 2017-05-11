#include "device.h"
#include "tact.h"
#include "spi.h"
#include "gtimer.h"
#include "ili9341.h"
#include "dma.h"

const uint16_t color []={0x0000, 0xF800, 0x001F, 0x07E0, 0x07FF, 0xF81F, 0xFFE0, 0xFFFF};

//Tact frq ;
extern "C"
{
	void DMA1_Channel2_3_IRQHandler ();
}

void DMA1_Channel2_3_IRQHandler ()
{
	DMA1->IFCR |= DMA_IFCR_CGIF3;
	GPIOA->ODR |=  1 << 4;
	DMA1_Channel3->CCR &=~ DMA_CCR_EN;
}

int main()
{

	
	//Dma spiDma (Dma::dmaChannel::ch3);
	
	
	Pin clk (Gpio::Port::A, 5, Gpio::Afmode::AF0);
	Pin miso (Gpio::Port::A, 6, Gpio::Afmode::AF0);
	Pin mosi (Gpio::Port::A, 7, Gpio::Afmode::AF0);
	/*Pin cs (Gpio::Port::A, 4, Gpio::Afmode::AF0);
	spi1.setCpol(Spi::cpol::neg);
	spi1.setCpha(Spi::cpha::first);
	spi1.setBaudrate(Spi::division::div8);
	spi1.setFsize(Spi::fsize::bit_16);*/
	//Spi spi1 ;
	//Ili9341 lcd (spi1, Gpio::Port::A, 1, Gpio::Port::A, 0);

	
	/*lcd.setDma (spiDma);
	DMA1_Channel3->CCR |= DMA_CCR_TCIE;
	NVIC_EnableIRQ (DMA1_Channel2_3_IRQn);*/
	
	while (1)
	{
		/*for (uint8_t i=0;i<8;++i)
		{
			lcd.fillScreen (color[i]);
			delay_ms (500);
		}*/
	}
}
