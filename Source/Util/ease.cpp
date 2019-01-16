#include "Util/ease.h"

namespace Ease
{
  float elasticEaseInOut(float t, float b, float c, float d)
  {
    if (t==0) return b;  if ((t/=d/2)==2) return b+c; 
    float p=d*(.3f*1.5f);
    float a=c; 
    float s=p/4;
    
    if (t < 1) {
      float postFix =a*pow(2,10*(t-=1)); // postIncrement is evil
      return -.5f*(postFix* sin( (t*d-s)*(2*M_PI)/p )) + b;
    } 
    float postFix =  a*pow(2,-10*(t-=1)); // postIncrement is evil
    return postFix * sin( (t*d-s)*(2*M_PI)/p )*.5f + c + b;
  }

  float elasticEaseIn(float t, float b, float c, float d)
  {
    if (t==0) return b;  if ((t/=d)==1) return b+c;  
    float p=d*.3f;
    float a=c; 
    float s=p/4;
    float postFix =a*pow(2,10*(t-=1)); // this is a fix, again, with post-increment operators
    return -(postFix * sin((t*d-s)*(2*M_PI)/p )) + b;
  }

  float elasticEaseOut(float t, float b, float c, float d)
  {
    if (t==0) return b;  if ((t/=d)==1) return b+c;  
	  float p=d*.3f;
	  float a=c; 
	  float s=p/4;
    return (a*pow(2,-10*t) * sin( (t*d-s)*(2*M_PI)/p ) + c + b); 
  }

  float quintEaseInOut(float t, float b, float c, float d)
  {
    t/=d/2;
	  if ((t) < 1) return c/2*t*t*t*t*t + b;
    t-=2;
    return c/2*((t)*t*t*t*t + 2) + b;
  }

  float quintEaseIn(float t, float b, float c, float d)
  {
    t/=d;
    return c*(t)*t*t*t*t + b;
  }

  float quintEaseOut(float t, float b, float c, float d)
  {
    t=t/d-1;
    return c*((t - 1)*t*t*t*t + 1) + b;
  }

  float cubicEaseIn (float t,float b , float c, float d) 
  {
    t/=d;
	  return c*(t)*t*t + b;
  }

  float cubicEaseOut(float t,float b , float c, float d) 
  {
    t=t/d-1;
    return c*((t)*t*t + 1) + b;
  }

  float cubicEaseInOut(float t,float b , float c, float d) 
  {
    t/=d/2;
    if ((t) < 1) return c/2*t*t*t + b;
    t-=2;
    return c/2*((t)*t*t + 2) + b;	
  }
} /* ease */
