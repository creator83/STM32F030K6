#include "pid.h"


/*! \brief Initialisation of PID controller parameters.
 *
 *  Initialise the variables used by the PID algorithm.
 *
 *  \param p_factor  Proportional term.
 *  \param i_factor  Integral term.
 *  \param d_factor  Derivate term.
 *  \param pid  Struct with PID status.
 */
 
 Pid::Pid (double P, double I, double D, uint16_t setPoint_)
 {
	 p = (uint16_t) (P*100);
	 i = (uint16_t) (I*100);
	 d = (uint16_t) (D*100);
	 sumError = lastProcessValue = 0;
	 maxError = MAX_INT / (p + 1);
	 maxSumError = MAX_I_TERM / (i + 1);
	 setPoint = setPoint_;
 }

/*! \brief PID control algorithm.
 *
 *  Calculates output from setpoint, process value and PID status.
 *
 *  \param setPoint  Desired value.
 *  \param processValue  Measured value.
 *  \param pid_st  PID status struct.
 */
uint16_t Pid::compute (uint16_t processValue)
 {
	 int16_t error, p_term, d_term;
	 int32_t i_term, ret, temp;
	 error = setPoint - processValue;
  // Calculate Pterm and limit error overflow
  if (error > maxError) p_term = MAX_INT;
  else if (error < -maxError) p_term = -MAX_INT;
  else p_term = p * error;

  // Calculate Iterm and limit integral runaway
  temp = sumError + error;
  if(temp > maxSumError)
	{
    i_term = MAX_I_TERM;
    sumError = maxSumError;
  }
  else if(temp < -maxSumError)
	{
    i_term = -MAX_I_TERM;
    sumError = -maxSumError;
  }
  else
	{
    sumError = temp;
    i_term = i * sumError;
  }	 
	
	// Calculate Dterm
  d_term = d * (lastProcessValue - processValue);

  lastProcessValue = processValue;

  ret = (p_term + i_term + d_term) / 100;
  if(ret > MAX_UINT) ret = MAX_UINT;
  else if(ret < 0)ret = 0;
    
  return (uint16_t) ret;
 }

 void Pid::reset ()
{
	sumError = 0;
}

