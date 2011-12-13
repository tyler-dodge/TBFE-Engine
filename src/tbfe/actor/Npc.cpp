#include "tbfe/actor/Npc.h"
//(PositionX, PositionY, Hair, Facial Hair, Hair Color, Torso, Frame Lengths, Frames,
//Number of Frames, Number Of Frame Sets)
Npc::Npc():Actor(0,0)
{
};
Npc::Npc(int PositionX,int PositionY,string PlayerConversation)
:Actor(PositionX,PositionY)
{
  setScriptSource("Actors/Npc/Npc.py");
  string StandAnimation="0,";
  Action Stand("Stand","");
  Animation Body("test.dae",StandAnimation,
		 0,0,1,true);
  Quaternion rotation=Quaternion(1,0,0,270);
  Body.setRotation(rotation);
  Stand.addAnimation(Body);
  Stand.setMainAnimation(0);
  addAction(Stand);
};
Npc::~Npc()
{
};
