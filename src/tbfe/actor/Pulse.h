#include "Actor.h"
#ifndef Pulse_L
#define Pulse_L

class Pulse:public Actor
{
 private:
  float distance_;
 public:
  Pulse(int, int,int,float,PositionF, float);
  ~Pulse();
  int collisionPulse();
  string getConversation(bool);
};
#endif
