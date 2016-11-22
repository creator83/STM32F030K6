#include "buffer.h"


const char Buffer::Array_char [11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '};
const char Buffer::ArraySegChar [11] = {0x3F ,0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D, 0x07 , 0x7F , 0x6F ,  0x00};
const char Buffer::ArraySegDpChar [11] = {0xBF , 0x86 , 0xDB , 0xCF , 0xE6 , 0xED , 0xFD , 0x87 , 0xFF , 0xEF , 0x00};

Buffer::Buffer()
{
	n = size;

}




uint8_t Buffer::getArraySize ()
{
	return n;
}


void Buffer::pars (const uint16_t & val)
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
  if (count<2)count = 2;
  for (uint8_t i=count-1;i<5;++i)
  {
    arr [i] = Array_char [arrVal[i]];
  }
  //arr [2] = ArraySegDpChar [arrVal[2]];
	real = &arr [(size-1)-count];

}


char * Buffer::getArray ()
{
	return arr;
}

char * Buffer::getContent ()
{
	return real;
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
