#include "device.h"                  // Device header

#ifndef DMA_H
#define DMA_H


class dma;

typedef void (dma::*PTR_DMA)() ;

class Dma
{
	//variables
public:
	enum class dmaChannel {ch1, ch2, ch3 , ch4, ch5};
	enum class direction {periph2mem, mem2periph};
	enum class size {bit8, bit16, bit32};
	enum class prioritet {Low, Medium, High, VHigh};
	enum class periph {SPI1_RX, SPI1_TX};
	
	
private:
 size memory_;
	size periph_;
 static DMA_Channel_TypeDef * dma_channel [5];
 static IRQn_Type intrpt [3];
 uint8_t channel_;
	//functions
public:	
	Dma ();
	Dma (dmaChannel ch);
	//dma (channel_ ch, size_ mem = bit8, size_ per = bit8);
	void setChannel (dmaChannel ch);
	void setSources (uint32_t  mem, uint32_t  per);
	void setPtrMem (uint32_t mem);
	void setPtrPeriph (uint32_t  per);
	void setLength (uint16_t length);
	void setSize (size m, size p);
	void setDirection (direction d);
	void setIncMem (bool state);
	void setIncPer (bool state);
	void setMemToMem (bool state);
	void interruptEnable ();
 void interruptDisable ();
	void setPrioritet (prioritet p);
	void start ();
	void stop ();
	void clearTcif ();
	bool flagTcif ();
	void clearTeif ();
	void clearHtif ();
	void clearGif ();
	void clearFlags ();
};

#endif
