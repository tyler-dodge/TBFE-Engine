#include "Npc.h"
//(PositionX, PositionY, Hair, Facial Hair, Hair Color, Torso, Frame Lengths, Frames,
//Number of Frames, Number Of Frame Sets)
Npc::Npc():Actor(0,0)
{
  setConversation("The programmers were too lazy to give me lines to say");
};
Npc::Npc(int PositionX,int PositionY,string PlayerConversation)
:Actor(PositionX,PositionY)
{
  setConversation(PlayerConversation);
  setScriptSource("Actors/Npc/Npc.py");
  string StandAnimation="0,";
  Action Stand("Stand","");
  Animation Body("test.dae",StandAnimation,
		 0,0,1,true);
  Body.setRotation(0,90,0);
  Stand.addAnimation(Body);
  Stand.setMainAnimation(0);
  addAction(Stand);
};
Npc::~Npc()
{
};
string Npc::getConversation(bool PlayerCheck)
{
  //TODO: conversation Lock test
  return conversation_;
};
