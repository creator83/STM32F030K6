#include "font.h"

Font::Font ()
:width (0), height (0), shift (0), font (nullptr)
{
 
}

Font::Font (uint16_t w, uint16_t h, uint16_t s, const uint8_t * f)
:width (w), height (h), shift (s), font (f)
{
}

void Font::setFont (uint8_t * f)
{
 font = f;
}

void Font::setWidth (uint16_t w)
{
 width = w;
}

void Font::setHeght (uint16_t h)
{
 height = h;
}

void Font::setShift (uint16_t s)
{
 shift = s;
}

uint16_t & Font::getWidth ()
{
 return width;
}

uint16_t & Font::getHeight ()
{
 return height;
}

uint16_t & Font::getShift ()
{
 return shift;
}

const uint8_t * Font::getFont()
{
 return font;
}