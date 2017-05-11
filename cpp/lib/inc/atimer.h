#include "device.h"                   // Device header
#include "tact.h"


#ifndef ATIMER_H
#define ATIMER_H


class Atimer
{
	//variables
public:
		enum nChannel {channel1, channel2, channel3, channel4};
		
private:
		
protected:

		nChannel ch_;
//functions
public:
		Atimer (uint16_t divider);
		Atimer (uint16_t divider, uint16_t arr);
		Atimer ();
		void setCnt (uint16_t);
		void setPsc (uint16_t);
		void setArr (uint16_t);
		void setChannelValue (uint16_t);
		void start ();
		void stop ();
		void clearTif();
		void clearUif();
		uint16_t getCnt ();
		
protected:
	
private:		

};
 
#endif
