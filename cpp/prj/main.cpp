#include "stm32f0xx.h"
#include "tact.h"
#include "spi.h"
#include "gtimer.h"
#include "ili9341.h"
#include "dma.h"

const uint16_t color []={0x0000, 0xF800, 0x001F, 0x07E0, 0x07FF, 0xF81F, 0xFFE0, 0xFFFF};

int main()
{

	Tact frq ;
 Dma spiDma (Dma::dmaChannel::ch3);
	Spi spi1;
	Pin clk (Gpio::Port::A, 5, Gpio::Afmode::AF0);
	Pin miso (Gpio::Port::A, 6, Gpio::Afmode::AF0);
	Pin mosi (Gpio::Port::A, 7, Gpio::Afmode::AF0);
	Ili9341 lcd (spi1, Gpio::Port::A, 1, Gpio::Port::A, 0);
	

 
	while (1)
	{
		for (uint8_t i=0;i<8;++i)
		{
			lcd.fillScreen (color[i]);
			delay_ms (500);
		}
	}
}
