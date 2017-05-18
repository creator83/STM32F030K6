#include "device.h"                // Device header
#include "ht1621.h"


#ifndef ROOMLCD_H
#define ROOMLCD_H

namespace roomLcdBits
{
 //uint16_t 
}
class Roomlcd
{
//variables
 
public:	
  enum class digitsPosition :uint16_t {dig1=0x0B0C, dig2=0x0D0E, dig3=0x1012, dig4=0x1314, dig5=0x0102, dig6=0x0304, dig7=0x0506, dig8= 0x0708};
  enum class pic :uint8_t {cool, heat, dry, fan, floor, set, in, no, room,out, value, temp, hum, tools, lock, h1, min1, percent1, c1, f1, h2, min2, percent2, c2, f2, fan1, aut, pb1, pb2, pb3, alarm, one, two, on, off};
private:
 static uint8_t digits [2][10];
 static uint8_t picS [37][2];
 static uint8_t buffer [32];
 Ht1621 * lcdDriver;

public:	
  Roomlcd (Ht1621 &);
  void setDigit (uint8_t val, digitsPosition n);
  void setPic (pic p);
  void clearPic (pic p);
private:
	
  
};


#endif


