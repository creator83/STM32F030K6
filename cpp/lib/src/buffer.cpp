#include "buffer.h"

const uint8_t Buffer::Array_char [10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};


Buffer::Buffer(uint8_t size)
{	
	n= size+1;
	arr = new char [n];
	//uint8_t *ptr = new
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
	uint8_t tous, hundr, dec, ones;
	uint16_t temp = val;
	count = 0;
	for (tous=0;temp>=1000;++tous, ++count)temp-=1000;
	for (hundr=0;temp>=100;++hundr, ++count)temp -=100;
	for (dec=0;temp>=10;++dec, ++count)temp -=10;
	ones = temp%10;
	++count;
		arr [0] = Array_char [tous];
		arr [1] = Array_char [ hundr];
		arr [2] = Array_char [dec];
		arr [3] = Array_char [ones];
		arr [n] = 0;

	/*arr [0] = Array_char [tous];
	arr [1] = Array_char [hundr];
	arr [2] = Array_char [dec];
	arr [3] = Array_char [ones];
	arr [count] = '\0';*/
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
