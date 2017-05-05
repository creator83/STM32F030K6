#include "device.h"


#ifndef PID_H
#define PID_H

// Maximum value of variables
const int16_t MAX_INT = 32767;
const uint16_t MAX_UINT = 0xFFFF;
const int32_t MAX_LONG = 2147483647;
const int32_t MAX_I_TERM = MAX_LONG/2;


class Pid 
{
private:
	//varibles
	uint16_t p, i, d;
	//! Last process value, used to find derivative of process value.
  int16_t lastProcessValue;
  //! Summation of errors, used for integrate calculations
  int32_t sumError;
  //! Maximum allowed error, avoid overflow
  int16_t maxError;
  //! Maximum allowed sumerror, avoid overflow
  int32_t maxSumError, ret;
  uint16_t setPoint;
  uint16_t pidLimit;
	//functions
public:
  Pid (double P, double I, double D, uint16_t setPoint_);
  uint16_t compute (uint16_t processValue);

  uint16_t & getP (){return p;}
  uint16_t & getI (){return i;}
  uint16_t & getD (){return d;}
  void setP (uint16_t);
  void setI (uint16_t);
  void setD (uint16_t);
  void setT (uint16_t);
  void setPidLimit (uint16_t);
  void reset ();
};

#endif
