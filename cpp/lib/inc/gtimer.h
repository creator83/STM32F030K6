#include "stm32f0xx.h"                  // Device header
#include "tact.h"


#ifndef GTIMER_H
#define GTIMER_H

class Gtimer;
typedef void(Gtimer::*PtrTimer)();

class Gtimer
{
	//variables
public:
		enum nTimer {Timer3, Timer14, Timer15, Timer16, Timer17};
		enum nChannel {channel1, channel2, channel3, channel4};
		
private:
		nTimer n_;
		nChannel ch_;
protected:
		static PtrTimer iniTimer [5];
		static TIM_TypeDef* timerBase [5];
//functions
public:
		Gtimer (nTimer n, uint16_t divider);
		Gtimer (nTimer n);
		void setCnt (uint16_t);
		void setPsc (uint16_t);
		void setArr (uint16_t);
		uint16_t getCnt ();
		void Start ();
		void Stop ();
		void ClearFlag();

private:
		void clockTimer3 ();
		void clockTimer14 ();
		void clockTimer15 ();
		void clockTimer16 ();
		void clockTimer17 ();
};
 
#endif
