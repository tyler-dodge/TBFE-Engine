#include "Actor.h"
#ifndef Pulse_L
#define Pulse_L

class Pulse:public Actor
{
 private:
  float distance_;
 public:
  Pulse(PositionF,float,Quaternion, float);
  ~Pulse();
  int collisionPulse();
};
#endif
