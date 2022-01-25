#ifndef PIDCTRL_H
#define PIDCTRL_H
#include "CircularBuffer.h"

class PIDCtrl
{
  public:
  // kp,ki,kd are the PID coefficients
  // ts is the sample interval
  // bufferSize is the maximum size of the data buffer
  PIDCtrl(float kp,float ki,float kd, float ts, int bufferSize=10);

  void SetCoefficients(float kp, float ki, float kd=0);
  float GetKp();
  float GetKi();
  float GetKd();
  float GetTs();

  // sets the time between successive samples
  void SetSampleInterval(float ts);

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

  float DeltaError();

  // returns the output of the PID, or the correction to be applied to the process
  float Correction();

  // returns the integral value
  float Integral();

  // Prints out the buffer
  void Print();

  bool BufferIsFull();
  
  private:
  int bufferSize;
  CircularBuffer<float> buffer;
  float kp,ki,kd,ts=1;
  float target;
  float sum;
  int dataIn=0;
};
#endif