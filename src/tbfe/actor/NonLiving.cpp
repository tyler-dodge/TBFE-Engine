#include "NonLiving.h"
NonLiving::NonLiving(int x, int y, ActorType NewType):Actor(x,y)
{  
  setConversation(NewType.Conversation);
  setScriptSource(NewType.Script);
  Action Stand("Stand","");
  Animation Main(NewType.Source,"0,",0,0,1,true);
  Main.setRotation(270,90,0);
  Stand.setMainAnimation(0);
  Stand.addAnimation(Main);
  addAction(Stand);
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
