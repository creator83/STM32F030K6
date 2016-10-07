#include "dma.h"

uint32_t dma::adr_channel [5] = {DMA1_Channel1_BASE, DMA1_Channel2_BASE, DMA1_Channel3_BASE, DMA1_Channel4_BASE, DMA1_Channel5_BASE};

void dma::set_sources (uint32_t * mem, uint32_t * per)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CMAR = (uint32_t)mem;
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CPAR = (uint32_t)per;
}

void dma::set_mem (uint32_t mem)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CMAR = (uint32_t)mem;

}

void dma::set_periph (uint32_t per)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CPAR = per;
}

void dma::set_destination (uint32_t  mem)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CPAR = mem;

}

void dma::spi1_tx ()
{
	SPI1->CR2 |= SPI_CR2_TXDMAEN;
}

void dma::spi1_rx ()
{
	
}

void dma::set_length (uint16_t length)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CNDTR = length;
}

void dma::set_inc_mem (bool state)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CCR &= ~DMA_CCR_MINC;
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CCR |= state << 7;
}

void dma::set_inc_per (bool state)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CCR &= ~DMA_CCR_PINC;
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CCR |= state << 6;
}

void dma::set_prior (prior p)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CCR &= ~ DMA_CCR_PL;
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CCR |= p << 12;
}


void dma::start ()
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CCR |= DMA_CCR_EN;
}

void dma::stop ()
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CCR &= ~DMA_CCR_EN;
}

void dma::clear_tcf_flag ()
{
	DMA1->IFCR |= tcf << (ch_<< 2);
}

void dma::clear_tef_flag ()
{
	DMA1->IFCR |= tef << (ch_<< 2);
}

void dma::clear_htf_flag ()
{
	DMA1->IFCR |= htf << (ch_<< 2);
}

void dma::clear_gif_flag ()
{
	DMA1->IFCR |= gif << (ch_<< 2);
}

void dma::clear_all_flag ()
{
	DMA1->IFCR |= 0x0F << (ch_<< 2);
}






