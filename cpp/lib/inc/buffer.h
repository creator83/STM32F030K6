#include "device.h"


#ifndef BUFFER_H
#define BUFFER_H

const char Array_char [11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '};
const char Array_dec [10] = {0,1,2,3,4,5,6,7,8,9};
const char hexChar [16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const char ArraySegChar [11] = {0x3F ,0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D, 0x07 , 0x7F , 0x6F ,  0x00};
//const char ArraySegDpChar [11] = {0xBF , 0x86 , 0xDB , 0xCF , 0xE6 , 0xED , 0xFD , 0x87 , 0xFF , 0xEF , 0x00};

const uint8_t sizeDivider = 5;

class Buffer
{
public:

private:
  uint8_t size;
  uint8_t count;
  char * arr;
  char * arrPtr;
  char * real;
  const char * font;
  static const uint16_t divider [sizeDivider];
public:
  Buffer(char *, char n);

  void parsDec16 (const uint16_t &);
  void parsDec16 (const uint16_t &, uint8_t n);
  void parsFloat (const uint16_t &);
  void parsFloatD (const uint16_t &);
  void parsHex32 (uint32_t value);
  bool setElement (uint8_t el, uint8_t val);
  uint8_t getArraySize ();
  char * getArray ();
  //char * getArray ();
  char * getContent ();
  char * getElement (uint8_t n);
  uint8_t getCount ();
  void setFont (const char *);
};

	
#endif
