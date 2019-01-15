#ifndef EASE__
#define EASE__
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
//all easing functions are taken from robert pennings easing equations
namespace Ease 
{
  float elasticEaseInOut(float t, float b = 0, float c = 1, float d = 1);
  float elasticEaseIn(float t, float b = 0, float c = 1, float d = 1);
  float elasticEaseOut(float t, float b = 0, float c = 1, float d = 1);
  float quintEaseInOut(float t, float b = 0, float c = 1, float d = 1);
  float quintEaseIn(float t, float b = 0, float c = 1, float d = 1);
  float quintEaseOut(float t, float b = 0, float c = 1, float d = 1);
  float cubicEaseOut(float t, float b = 0, float c = 1, float d = 1);
  float cubicEaseIn(float t, float b = 0, float c = 1, float d = 1);
  float cubicEaseInOut(float t, float b = 0, float c = 1, float d = 1);
}

#endif