#include "Actor.h"
#ifndef NonLiving_L
#define NonLiving_L

class NonLiving:public Actor
{
 private:
 public:
  NonLiving(int, int,ActorType);
  ~NonLiving();
};
#endif
