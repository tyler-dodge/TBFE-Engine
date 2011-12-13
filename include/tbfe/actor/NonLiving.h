#ifndef NonLiving_L
#define NonLiving_L
#include <boost/python.hpp>
#include "tbfe/actor/Actor.h"
class NonLiving:public Actor
{
 private:
 public:
  NonLiving(int, int,ActorType);
  ~NonLiving();
};
#endif
