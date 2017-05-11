#include "segled.h"

uint8_t Segled::number [13] = {0x3F ,0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D, 0x07 , 0x7F , 0x6F ,  0x00, 0x60, 0x6A};
uint8_t Segled::numberDp [13] = {0xBF , 0x86 , 0xDB , 0xCF , 0xE6 , 0xED , 0xFD , 0x87 , 0xFF , 0xEF , 0x00, 0x60, 0x6A};


Segled::Segled (uint8_t nDigit)
:segA (segledDef::segAport, segledDef::segApin), segB (segledDef::segBport, segledDef::segBpin), segC (segledDef::segCport, segledDef::segCpin), segD (segledDef::segDport, segledDef::segDpin), segE (segledDef::segEport, segledDef::segEpin), segF (segledDef::segFport, segledDef::segFpin), segG (segledDef::segGport, segledDef::segGpin), segDp (segledDef::segDpport, segledDef::segDppin),
dig1 (segledDef::digit1port, segledDef::digit1pin), dig2 (segledDef::digit2port, segledDef::digit2pin), dig3 (segledDef::digit3port, segledDef::digit3pin), dig4 (segledDef::digit4port, segledDef::digit4pin)
{
  N = nDigit;
  //Settings pin
  
  segments [0] = &segA;
  segments [1] = &segB;
  segments [2] = &segC;
  segments [3] = &segD;
  segments [4] = &segE;
  segments [5] = &segF;
  segments [6] = &segG;
  segments [7] = &segDp;
  
  digits [0] =  &dig1;
  digits [1] =  &dig2;
  digits [2] =  &dig3;
  digits [3] =  &dig4;
    
  segPins [0] = segledDef::segApin;
  segPins [1] = segledDef::segBpin;
  segPins [2] = segledDef::segCpin;
  segPins [3] = segledDef::segDpin;
  segPins [4] = segledDef::segEpin;
  segPins [5] = segledDef::segFpin;
  segPins [6] = segledDef::segGpin;
  segPins [7] = segledDef::segDppin;
  
  digPins [0] = segledDef::digit1pin;
  digPins [1] = segledDef::digit2pin;
  digPins [2] = segledDef::digit3pin;
  digPins [3] = segledDef::digit4pin;
}


void Segled::setSegments (char * val)
{
  for (uint8_t i=0; i<8; ++i)  
  {
    if (*val& 1<<i) segments [i]->set ();
    else segments [i]->clear ();
  }
}

void Segled::clearSegments ()
{
  for (uint8_t i=0;i<8;++i) segments [i]->clear ();
}

void Segled::setDigit (uint8_t d)
{
  digits[d]->set ();
}

void Segled::clearDigits ()
{
  for (uint8_t i=0;i<N;++i) digits [i]->clear ();
}

void Segled::frame (char * val, uint8_t d)
{
  clearSegments();
  clearDigits ();
  setSegments (val);
  setDigit (d);
}

void Segled::blink (char * val, uint8_t d, uint16_t period)
{
	static uint16_t counter=0;
	counter++;
	static bool flag;

	if (counter>period)
	{
		flag ^= 1;
		counter = 0;
	}
	if (flag)
	{
		frame (val, d);
		return ;
	}
	clearDigits ();
}

void Segled::value (char * val, uint8_t n)
{
  clearSegments();
  clearDigits ();
  static uint8_t i;
  if (i<n)
  {
	  setSegments (&val[i]);
	  setDigit (i);
	  ++i;
  }
  else
  {
	  i=0;
	  setSegments (&val[i]);
	  setDigit (i);
	  ++i;
  }

}
