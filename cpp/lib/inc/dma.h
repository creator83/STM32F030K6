#include "stm32f0xx.h"                  // Device header

#ifndef DMA_H
#define DMA_H


class dma;

typedef void (dma::*PTR_DMA)() ;

class Dma
{
	//variables
public:
	enum dmaChannel {ch1, ch2, ch3 , ch4, ch5};
	enum direction {periph2mem, mem2periph};
	enum size {bit8, bit16, bit32};
	enum flags_ {gif = 1, tcf = 2, htf = 4, tef = 8};
	enum prioritet {Low, Medium, High, VHigh};
	enum periph {SPI1_RX, SPI1_TX};
	dmaChannel channel_;
	size memory_;
	size periph_;
	static DMA_Channel_TypeDef * dma_channel [5];

	//functions
public:	
	Dma (){}
	Dma (dmaChannel ch);
	//dma (channel_ ch, size_ mem = bit8, size_ per = bit8);
	void setSources (uint32_t * mem, uint32_t * per);
	void setPtrMem (uint32_t * mem);
	void setPtrPeriph (uint32_t * per);
	void setLength (uint16_t length);
	void setIncMem (bool state);
	void setIncPer (bool state);
	void setMemToMem (bool state);
	void setPrioritet (prioritet p);
	void start ();
	void stop ();
	void clearTcif ();
	void clearTeif ();
	void clearHtif ();
	void clearGif ();
	void clearFlags ();
};

#endif
