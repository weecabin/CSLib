#ifndef NAVIGATION_H
#define NAVIGATION_H

float FixHeading(float heading)
{
  while(heading<0)heading+=360;
  while(heading>360)heading-=360;
  return heading;
}
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