#include "stm32f0xx.h"  



#ifndef PID_H
#define PID_H

// Maximum value of variables
const int16_t MAX_INT = 32767;
const int16_t MAX_UINT = 0xFFFF;
const int32_t MAX_LONG = 2147483647;
const int32_t MAX_I_TERM = MAX_LONG/2;


class Pid 
{
	//varibles
	uint16_t p, i, d;
	//! Last process value, used to find derivative of process value.
  int16_t lastProcessValue;
  //! Summation of errors, used for integrate calculations
  int32_t sumError;
  //! Maximum allowed error, avoid overflow
  int16_t maxError;
  //! Maximum allowed sumerror, avoid overflow
  int32_t maxSumError;
	uint16_t setPoint;
	//functions
public:
	Pid (double P, double I, double D, uint16_t setPoint_);
	uint16_t compute (uint16_t processValue);
	void reset ();
};

#endif
