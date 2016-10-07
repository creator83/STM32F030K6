#include "stm32f0xx.h"                  // Device header

#ifndef DMA_H
#define DMA_H


class dma;

typedef void (dma::*PTR_DMA)() ;

class dma
{
	//variables
public:
	enum channel_ {ch1, ch2, ch3 , ch4, ch5};
	enum mode_ {periph2mem, mem2periph};
	enum size_ {bit8, bit16, bit32};
	enum flags_ {gif = 1, tcf = 2, htf = 4, tef = 8};
	enum prior {Low, Medium, High, VHigh};
	enum periph_ {SPI1_RX, SPI1_TX};
	uint32_t ch_;
	uint8_t size_mem;
	uint8_t size_periph;
	static uint32_t adr_channel [5];
	static PTR_DMA ptr_periph[2];
	//functions
public:	
	dma (channel_ ch, mode_ m, periph_ p, size_ mem = bit8, size_ per = bit8);
	dma (channel_ ch, size_ mem = bit8, size_ per = bit8);
	void set_sources (uint32_t * mem, uint32_t * per);
	void set_mem (uint32_t mem);
	void set_periph (uint32_t per);
	void set_destination (uint32_t mem);
	void set_length (uint16_t length);
	void set_inc_mem (bool state);
	void set_inc_per (bool state);
	void set_prior (prior p);
	void start ();
	void stop ();
	void clear_tcf_flag ();
	void clear_tef_flag ();
	void clear_htf_flag ();
	void clear_gif_flag ();
	void clear_all_flag ();
	void spi1_tx ();
	void spi1_rx ();
};

#endif
