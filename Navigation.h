#ifndef NAVIGATION_H
#define NAVIGATION_H

/*
maps heading to values between 0+ and 360;
0 is converted to 360
*/
float FixHeading(float heading)
{
  while(heading<=0)heading+=360;
  while(heading>360)heading-=360;
  return heading;
}

/*
returns the error relative to target.
not necessary to FixHeading before calling since this function calls FixHeading for both parameters
*/
float HeadingError(float target, float actual)
{
  target = FixHeading(target);
  actual = FixHeading(actual);
  float diff = actual-target;
  if (diff>180.0)diff=diff-360.0;
  if (diff<-180.0)diff+=360.0;
  return diff;
}
#endif