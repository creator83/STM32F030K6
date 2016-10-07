#include "dma.h"

DMA_Channel_TypeDef * Dma::dma_channel [5] = {DMA1_Channel1, DMA1_Channel2, DMA1_Channel3, DMA1_Channel4, DMA1_Channel5};




Dma::Dma (dmaChannel ch)
{
	channel_ = ch;
	RCC->AHBENR |= RCC_AHBENR_DMAEN;
	//dma_channel [channel_]->CCR &= ~(DMA_CCR_PSIZE|DMA_CCR_MSIZE|DMA_CCR_DIR);
	//dma_channel [channel_]->CCR |= (mem << 10|per << 8|m << 4)|DMA_CCR_TCIE;
}

void Dma::setSources (uint32_t * mem, uint32_t * per)
{
	dma_channel [channel_]->CMAR = (uint32_t)mem;
	dma_channel [channel_]->CPAR = (uint32_t)per;
}

void Dma::setPtrMem (uint32_t * mem)
{
	dma_channel [channel_]->CMAR = (uint32_t)mem;

}

void Dma::setPtrPeriph (uint32_t * per)
{
	dma_channel [channel_]->CPAR = (uint32_t)per;
}

void Dma::setLength (uint16_t length)
{
	dma_channel [channel_]->CNDTR = length;
}

void Dma::setIncMem (bool state)
{
	dma_channel [channel_]->CCR &= ~DMA_CCR_MINC;
	dma_channel [channel_]->CCR |= state << 7;
}

void Dma::setIncPer (bool state)
{
	dma_channel [channel_]->CCR &= ~DMA_CCR_PINC;
	dma_channel [channel_]->CCR |= state << 6;
}

void Dma::setMemToMem (bool state)
{
	dma_channel [channel_]->CCR &= ~ DMA_CCR_MEM2MEM;
	dma_channel [channel_]->CCR |= state << 14;
}

void Dma::setPrioritet (prioritet p)
{
	dma_channel [channel_]->CCR &= ~ DMA_CCR_PL;
	dma_channel [channel_]->CCR |= p << 12;
}


void Dma::start ()
{
	dma_channel [channel_]->CCR |= DMA_CCR_EN;
}

void Dma::stop ()
{
	dma_channel [channel_]->CCR &= ~DMA_CCR_EN;
}

void Dma::clearTcif ()
{
	DMA1->IFCR |= 1 << (((channel_-1)*4)+1);
}

void Dma::clearTeif ()
{
	DMA1->IFCR |= 1 << (((channel_-1)*4)+3);
}

void Dma::clearHtif ()
{
	DMA1->IFCR |= 1 << (((channel_-1)*4)+2);
}

void Dma::clearGif ()
{
	DMA1->IFCR |= 1 << (((channel_-1)*4));
}

void Dma::clearFlags ()
{
	DMA1->IFCR |= 1 << (((channel_-1)*4)+3);
}






