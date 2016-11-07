#include "stm32f0xx.h"


#ifndef BUFFER_H
#define BUFFER_H

const char size  = 6;

class Buffer
{
public:
	
private:
	uint8_t n;
	uint8_t count;
	char arr[size];
  char * real;
	static const char Array_char [11];
	static const char ArraySegChar [11];
	static const char ArraySegDpChar [11];
public:
	Buffer();

	void pars (const uint16_t &);
	bool setElement (uint8_t el, uint8_t val);
	uint8_t getArraySize ();
	char * getArray ();
	char * getContent ();
	char * getElement (uint8_t n);
};

	
#endif
