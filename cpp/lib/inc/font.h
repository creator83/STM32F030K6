#include "stm32f0xx.h"

#ifndef FONT_H
#define FONT_H

class Font
{
 const uint8_t * font;
	uint16_t width;
	uint16_t height;
	uint16_t shift;
public:
 Font ();
 Font (uint16_t w, uint16_t h, uint16_t s, const uint8_t * f);
 void setFont (uint8_t * f);
 void setWidth (uint16_t);
 void setHeght (uint16_t);
 void setShift (uint16_t);
 uint16_t & getWidth ();
 uint16_t & getHeight ();
 uint16_t & getShift ();
 const uint8_t * getFont();
};

 
#endif
