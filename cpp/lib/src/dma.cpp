#include "dma.h"

DMA_Channel_TypeDef * Dma::dma_channel [5] = {DMA1_Channel1, DMA1_Channel2, DMA1_Channel3, DMA1_Channel4, DMA1_Channel5};


Dma::Dma ()
{
	RCC->AHBENR |= RCC_AHBENR_DMAEN;
}

Dma::Dma (dmaChannel ch)
{
	channel_ = static_cast <uint8_t> (ch);
	RCC->AHBENR |= RCC_AHBENR_DMAEN;
	//dma_channel [channel_]->CCR &= ~(DMA_CCR_PSIZE|DMA_CCR_MSIZE|DMA_CCR_DIR);
	//dma_channel [channel_]->CCR |= (mem << 10|per << 8|m << 4)|DMA_CCR_TCIE;
}

void Dma::setChannel (dmaChannel ch)
{
	channel_ = static_cast <uint8_t> (ch);
}

void Dma::setSources (uint32_t  mem, uint32_t  per)
{
	dma_channel [channel_]->CMAR = mem;
	dma_channel [channel_]->CPAR = per;
}

void Dma::setPtrMem (uint32_t  mem)
{
	dma_channel [channel_]->CMAR = mem;

}

void Dma::setPtrPeriph (uint32_t  per)
{
	dma_channel [channel_]->CPAR =  per;
}

void Dma::setLength (uint16_t length)
{
	dma_channel [channel_]->CNDTR = length;
}

void Dma::setSize (size m, size p)
{
	dma_channel [channel_]->CCR &= ~(DMA_CCR_PSIZE|DMA_CCR_MSIZE);
	dma_channel [channel_]->CCR |= (static_cast <uint8_t> (m) << 10|static_cast <uint8_t> (p) << 8);
}

void Dma::setDirection (direction d)
{
	dma_channel [channel_]->CCR &= ~DMA_CCR_DIR;
	dma_channel [channel_]->CCR |= static_cast <uint8_t> (d) << 4;
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

void Dma::setInterrupt (bool state)
{
	//dma_channel [channel_]->CCR &= ~
}

void Dma::setPrioritet (prioritet p)
{
	dma_channel [channel_]->CCR &= ~ DMA_CCR_PL;
	dma_channel [channel_]->CCR |= static_cast <uint8_t> (p) << 12;
}


void Dma::start ()
{
	dma_channel [channel_]->CCR |= DMA_CCR_EN;
}

void Dma::stop ()
{
	dma_channel [channel_]->CCR &= ~DMA_CCR_EN;
}

bool Dma::flagTcif ()
{
	return (DMA1->ISR&(2 << (((channel_)*4))));
}

void Dma::clearTcif ()
{
	DMA1->IFCR |= 2 << (((channel_)*4));
}

void Dma::clearTeif ()
{
	DMA1->IFCR |= 8 << (((channel_)*4));
}

void Dma::clearHtif ()
{
	DMA1->IFCR |= 4 << (((channel_)*4));
}

void Dma::clearFlags ()
{
	DMA1->IFCR |= 1 << (((channel_)*4));
}






