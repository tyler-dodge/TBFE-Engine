#include "NonLiving.h"
NonLiving::NonLiving(int x, int y, ActorType NewType):Actor(x,y)
{  
  setDirection(UP);
  setConversation(NewType.Conversation);
  setCollisionMap(NewType.Collision);
  setScriptSource(NewType.Script);
};
NonLiving::~NonLiving()
{
};
string NonLiving::getConversation(bool PlayerCheck)
{
  
  if (!PlayerCheck)
    {
    };
  return conversation_;
};
