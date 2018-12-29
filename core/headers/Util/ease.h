#ifndef EASE__
#define EASE__
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

namespace Ease 
{
  float elasticEaseInOut(float t, float b = 0, float c = 1, float d = 1);
  float elasticEaseIn(float t, float b = 0, float c = 1, float d = 1);
  float elasticEaseOut(float t, float b = 0, float c = 1, float d = 1);
}

#endif