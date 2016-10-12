#include "stm32f0xx.h"


#ifndef BUFFER_H
#define BUFFER_H

class Buffer
{
public:
	static const uint8_t Array_char [11];
private:
	uint8_t n;
	uint8_t count;
	char * arr ;
	char * real;
public:
	Buffer(uint8_t size);
	Buffer();
	~Buffer ();
	void pars (const uint16_t &);
	bool setElement (uint8_t el, uint8_t val);
	uint8_t getArraySize ();
	char * getArray ();
	char * getElement (uint8_t n);
};

	
#endif
