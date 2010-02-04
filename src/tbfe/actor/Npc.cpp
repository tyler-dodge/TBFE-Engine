#include "Npc.h"
//(PositionX, PositionY, Hair, Facial Hair, Hair Color, Torso, Frame Lengths, Frames,
//Number of Frames, Number Of Frame Sets)
Npc::Npc():Actor(0,0)
{
  setSpeed(3);
  setConversation("The programmers were too lazy to give me lines to say");
  setCollisionMap("Actors/living/Collision.png");
};
Npc::Npc(int PositionX,int PositionY,string PlayerConversation)
:Actor(PositionX,PositionY)
{
  setSpeed(3);
  setConversation(PlayerConversation);
  setScriptSource("Actors/Npc/Npc.lua");
  setCollisionMap("Actors/living/Collision.png");
};
Npc::~Npc()
{
};
string Npc::getConversation(bool PlayerCheck)
{
  //TODO: conversation Lock test
  return conversation_;
};
