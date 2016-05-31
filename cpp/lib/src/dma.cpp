#include "dma.h"

uint32_t dma::adr_channel [5] = {DMA1_Channel1_BASE, DMA1_Channel2_BASE, DMA1_Channel3_BASE, DMA1_Channel4_BASE, DMA1_Channel5_BASE};

dma::dma (channel_ ch, mode_ m, size_ mem, size_ per)
{
	ch_ = ch;
	size_mem = mem;
	size_periph = per;
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CCR &= ~(DMA_CCR_PSIZE|DMA_CCR_MSIZE|DMA_CCR_DIR);
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CCR |= (size_mem << 10|size_periph << 8|m << 4)|DMA_CCR_TCIE;
}



void dma::set_sources (uint32_t * mem, uint32_t * per)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CMAR = (uint32_t)mem;
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CPAR = (uint32_t)per;

	
}

void dma::set_source (uint32_t * mem)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CMAR = (uint32_t)mem;

}

void dma::set_destination (uint32_t * mem)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CPAR = (uint32_t)mem;

}

void dma::set_length (uint16_t length)
{
	((DMA_Channel_TypeDef *)adr_channel [ch_])->CNDTR = length;
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






