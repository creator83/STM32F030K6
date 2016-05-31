#include "stm32f0xx.h"                  // Device header

#ifndef DMA_H
#define DMA_H

typedef unsigned int* reg;

class dma
{
	//variables
public:
	enum channel_ {ch1, ch2, ch3 , ch4, ch5};
	enum mode_ {periph2mem, mem2periph};
	enum size_ {bit8, bit16, bit32};
	enum flags_ {gif = 1, tcf = 2, htf = 4, tef = 8};
	uint32_t ch_;
	uint8_t size_mem;
	uint8_t size_periph;
	static uint32_t adr_channel [5];
	//functions
public:	
	dma (channel_ ch, mode_ m, size_ mem = bit8, size_ per = bit8);
	dma (channel_ ch, size_ mem = bit8, size_ per = bit8);
	void set_sources (uint32_t * mem, uint32_t * per);
	void set_source (uint32_t * mem);
	void set_destination (uint32_t * mem);
	void set_length (uint16_t length);
	void start ();
	void stop ();
	void clear_tcf_flag ();
	void clear_tef_flag ();
	void clear_htf_flag ();
	void clear_gif_flag ();
	void clear_all_flag ();
};

#endif
