#include "Actor.h"
#ifndef Npc_L
#define Npc_L
using namespace std;
class Npc:public Actor
{
 private:
 public: 
  //Initializes NPC with stock conversation
  Npc();
  
  //Initializes NPC with position and conversation
  Npc(int,int,string,int,int,HairColor,int);
  
  ~Npc();
  //returns conversation
  string getConversation(bool);
};
#endif
