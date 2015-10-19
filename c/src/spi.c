#include "spi.h"


void init_spi ()
{
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//===Settings pins===//
	GPIOA->MODER &= ~(GPIO_MODER_MODER4|GPIO_MODER_MODER5|GPIO_MODER_MODER6|GPIO_MODER_MODER7);

	//CS
	GPIOA->MODER |= GPIO_MODER_MODER4_0;
	//GPIOA->MODER |= GPIO_MODER_MODER4_1;
	
	//SCK
	GPIOA->MODER |= GPIO_MODER_MODER5_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR5;
	
	//MISO
	GPIOA->MODER |= GPIO_MODER_MODER6_1;
	
	//MOSI
	GPIOA->MODER |= GPIO_MODER_MODER7_1;
	
	//High CS
	GPIOA->ODR |= 1 << CS;
	
	
	SPI1->CR1 = SPI_CR1_MSTR |  SPI_CR1_BR; 
SPI1->CR2 = SPI_CR2_SSOE |  SPI_CR2_RXNEIE |  SPI_CR2_FRXTH
 |  SPI_CR2_DS_2 |  SPI_CR2_DS_1 |  SPI_CR2_DS_0; 
SPI1->CR1 |= SPI_CR1_SPE;
	/*
	//===Settings SPI===//
	//SPI1->CR1 = 0;
	
	//Master or Slave
	SPI1->CR1 |= SPI_CR1_MSTR;
	
	//CPOL
	SPI1->CR1 |= SPI_CR1_CPOL;
	
	//CPHA
	SPI1->CR1 |= SPI_CR1_CPHA;
	
	//Division
	SPI1->CR1 |= SPI_CR1_BR
	//SPI_CR1_BR_0|
	//SPI_CR1_BR_2; //64
	;
	//Soft mode CS
	 SPI1->CR1 |= SPI_CR1_SSM ;
   SPI1->CR1 |= SPI_CR1_SSI ;
	 //SPI1->CR2 |= SPI_CR2_SSOE |  SPI_CR2_RXNEIE |  SPI_CR2_FRXTH|  SPI_CR2_DS_2 |  SPI_CR2_DS_1 |  SPI_CR2_DS_0;
	 
	 //Turn on Spi
	 SPI1->CR1 |= SPI_CR1_SPE;*/
}



uint8_t transfer (uint8_t data)
{
	while (SPI1->SR&SPI_SR_BSY);
	*(uint8_t *)&(SPI1->DR) = data;
	return (uint8_t)SPI1->DR;
}

void set_cs (void)
{
	GPIOA->ODR |= 1 << CS;
}
 
void clear_cs (void)
{
	GPIOA->ODR &= ~(1 << CS);
}

