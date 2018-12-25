#include "Game/Object/sinkAble.h"
#include "System/Physics/collisionModule.h"

float ease(float t,float b , float c, float d)
{
    if (t==0) return b;  if ((t/=d)==1) return b+c;  
    float p=d*.3f;
    float a=c; 
    float s=p/4;
    return (a*pow(2,-10*t) * sin( (t*d-s)*(2*M_PI)/p ) + c + b);  
    // if(t <= 0.5f)
    //   return 2.0f * pow(t, 2);
    // t -= 0.5f;
    // return 2.0f * t * (1.0f - t) + 0.5;
}
	
float easeIn (float t,float b , float c, float d) {
	if (t==0) return b;  if ((t/=d)==1) return b+c;  
	float p=d*.3f;
	float a=c; 
	float s=p/4;
	float postFix =a*pow(2,10*(t-=1)); // this is a fix, again, with post-increment operators
	return -(postFix * sin((t*d-s)*(2*M_PI)/p )) + b;
}
 
float easeOut(float t,float b , float c, float d) {
	if (t==0) return b;  if ((t/=d)==1) return b+c;  
	float p=d*.3f;
	float a=c; 
	float s=p/4;
	return (a*pow(2,-10*t) * sin( (t*d-s)*(2*M_PI)/p ) + c + b);	
}
SinkAble::SinkAble(Vec3<float> * position, float sinkDistance, double & deltaTime, Object * object) : Component(object), dt(deltaTime)
{
  targetPos = position;
  lowestY = (*position)[1] - sinkDistance;
  originalY = (*position)[1];
  object->subscribe("collision", this);
}

SinkAble::~SinkAble()
{

}

void SinkAble::update()
{
  passedTime += (dt * 0.2) * ((hit || lastHit) ? -1 : 1);
  if (hit != lastHit && std::fabs(passedTime) > 0.4) passedTime = 0.4;
  if (passedTime > 0.4) passedTime = 0.4;
  if (passedTime < -0.4) passedTime = -0.4;
  (*targetPos)[1] = ease(std::fabs(passedTime), 0, 1, 1) * originalY + (1.0 - ease(std::fabs(passedTime), 0, 1, 1)) * lowestY;
  lastHit = hit;
  hit = false;
}

void SinkAble::receiveMessage(const std::string & name, void* data)
{
  if (name == "collision") {
    CollisionData * coll = static_cast<CollisionData*>(data);
    if (coll->firstResolution[1] != 0) {
      hit = true;
    }
  }
}