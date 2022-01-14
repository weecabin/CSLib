#ifndef PIDCTRL_H
#define PIDCTRL_H
#include "CircularBuffer.h"

class PIDCtrl
{
  public:
  PIDCtrl(float kp,float ki,float kd, int bufferSize=10);

  void SetCoefficients(float kp, float ki, float kd=0);
  float GetKp();
  float GetKi();
  float GetKd();
   
  // The following two methods are used when the input is the current value of the process
  // Enter the target of the PID
  void Target(float target);
  
  // Enter the current value of the process
  // This function will subtract the target from current value of the process
  // and add the result to the PID
  float Add(float value);

  // Use this if the error is a complex function, best handled by the calling routine
  // This should be the error for the PID calculated by the calling routine
  // the internal target value isn't used
  float NextError(float error);

  // returns the output of the PID, or the correction to be applied to the process
  float Correction();

  // returns the integral value
  float Integral();

  // Prints out the buffer
  void Print();
  
  private:
  CircularBuffer<float> buffer;
  float kp,ki,kd;
  float target;
  float sum;
};
#endif