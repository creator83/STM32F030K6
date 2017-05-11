#include "buffer.h"



const uint16_t Buffer::divider [sizeDivider] = {10000, 1000, 100, 10};

Buffer::Buffer(char *a, char n_)
:size (n_), arr(a), arrPtr(a)
{
	
}



uint8_t Buffer::getArraySize ()
{
	return size;
}


void Buffer::parsDec16 (const uint16_t & val)
{
    uint8_t arrVal[5] = {0};
	uint16_t temp = val;
    uint8_t * tempPtr = arrVal;
	count = 5;

	for (arrVal[0]=0;temp>=10000;++arrVal[0]) temp -= 10000;
	
	for (arrVal[1]=0;temp>=1000;++arrVal[1])temp-=1000;
	
	for (arrVal[2]=0;temp>=100;++arrVal[2])temp -=100;
	
	for (arrVal[3]=0;temp>=10;++arrVal[3])temp -=10;
	
	arrVal[4] = temp%10;
        
    while (!*tempPtr++)
    {
    	--count;
    }
    if (count<1)count = 1;
    arr = arrPtr;
    for (uint8_t i=0; i<size; ++i)
    {
    	*arr++ = font [arrVal[i]];
    }
     /*
    for (uint8_t i=size-1-count, j=5-count;j<5;++i,++j)
    {
    	arr [i] = font [arrVal[j]];
    }*/

    if (arrVal [2] ==0) arr [2] = font [10];
        
        //arr [3] = ArraySegDpChar [arrVal[3]];
    real = &arr [(size-1)-count];
}

void Buffer::parsDec16 (const uint16_t & val, uint8_t n)
{
  uint8_t arrVal[5] = {0};
  uint16_t temp = val;
  uint8_t k = sizeDivider-n;
	arr = arrPtr;
  for (uint8_t i=0;i<n-1;++i)
  {
    for (arrVal[k+i]=0;temp>=divider[k+i]; ++arrVal[k+i]) temp-= divider[k+i];
    *arr++ = font [arrVal[k+i]];
  }
	
  *arr = font [temp];
}

void Buffer::parsFloat (const uint16_t & val)
{
  uint8_t arrVal[2] = {0};
  uint16_t temp = val;
  for (arrVal[0]=0;temp>=10;++arrVal[0])temp -=10;
  arrVal [1] = temp%10;
  arr [2] = font [arrVal [0]];
  arr [3] = '.';
  arr [4] = font [arrVal [1]];
}

void Buffer::parsFloatD (const uint16_t & val)
{
  uint8_t arrVal[3] = {0};
  uint16_t temp = val;
  for (arrVal[0]=0;temp>=100;++arrVal[0])temp -=100;
  for (arrVal[1]=0;temp>=10;++arrVal[1])temp -=10;
  arrVal [2] = temp%10;
  if (arrVal [0]==0) arr [1] = font [10];
  else arr [1] = font [arrVal [0]];
  arr [2] = font [arrVal [1]];
  arr [3] = '.';
  arr [4] = font [arrVal [2]];
}

void Buffer::parsHex32 (uint32_t value)
{
  arr [0] = hexChar [(value&0xF0000000)>>28];
  arr [1] = hexChar [(value&0x0F000000)>>24];
  arr [2] = hexChar [(value&0x00F00000)>>20];
  arr [3] = hexChar [(value&0x000F0000)>>16];
  arr [4] = hexChar [(value&0x0000F000)>>12];
  arr [5] = hexChar [(value&0x00000F00)>>8];
 /* arr [6] = hexChar [(value&0x000000F0)>>4];
  arr [7] = hexChar [value&0x0F];*/
}


char * Buffer::getArray ()
{
  return arrPtr;
}

char * Buffer::getContent ()
{
  return real;
}

char * Buffer::getElement (uint8_t n)
{
	arr = arrPtr;
	return &arr[n];
}


bool Buffer::setElement (uint8_t el, uint8_t val)
{
	if (el>(size-1)) return false;
	else
	{
		arr [el] = val;
		return true;
	}
}

uint8_t Buffer::getCount ()
{
  return count;
}

void Buffer::setFont (const char *f)
{
  font = f;
}

