#include "buffer.h"

const uint8_t Buffer::Array_char [11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '};


Buffer::Buffer(uint8_t size)
{	
	n= size+1;
	arr = new char [n];
	//uint8_t *ptr = new
}

Buffer::Buffer()
{
	n = 6;
	arr = new char [n];
	arr [n-1] = 0;
}

Buffer::~Buffer ()
{
	delete [] arr;
}

uint8_t Buffer::getArraySize ()
{
	return n;
}

void Buffer::pars (const uint16_t & val)
{
	uint8_t tTous, tous, hundr, dec, ones;
	uint16_t temp = val;
	count = 1;
	for (tTous=0;temp>=10000;++tTous) temp -= 10000;
	//if (tTous)++count;
	for (tous=0;temp>=1000;++tous, ++count)temp-=1000;
	//if (tous) ++count;
	for (hundr=0;temp>=100;++hundr, ++count)temp -=100;
	//if (hundr) ++count;
	for (dec=0;temp>=10;++dec, ++count)temp -=10;
	//if (dec) ++count;
	ones = temp%10;
	++count;
			arr [0] = Array_char [tTous];
			arr [1] = Array_char [tous];
			arr [2] = Array_char [hundr];
			arr [3] = Array_char [dec];
			arr [4] = Array_char [ones];
			//real = &arr [n-1-count];
}

char * Buffer::getArray ()
{
	return arr;
}

char * Buffer::getElement (uint8_t n)
{
	return &arr[n];
}

bool Buffer::setElement (uint8_t el, uint8_t val)
{
	if (el>(n-1)) return false;
	else
	{
		arr [el] = val;
		return true;
	}
}
