#include "Base.h"
TBFE_Base::TBFE_Base()
{
};
TBFE_Base::~TBFE_Base()
{
};
SDL_Surface * TBFE_Base::CollisionTile=NULL;
Console TBFE_Base::MainConsole;
vector<Actor *> TBFE_Base::ActorList;
vector<Window *> TBFE_Base::WindowList;
Position TBFE_Base::ScreenDimensions;
int TBFE_Base::TileSize=100;
int TBFE_Base::NumberOfActors;  
bool TBFE_Base::KeyControl;
Map TBFE_Base::CurrentMap;
int TBFE_Base::Time;
Actor * TBFE_Base::Talker;
Actor * TBFE_Base::MainPlayer=NULL;
TTF_Font * TBFE_Base::font;
Element * TBFE_Base::KeyTarget;
float TBFE_Base::GameSpeed=1;
vector<AnimationSheet> TBFE_Base::AnimationSheets;
int GetActorNum(Actor *actorPtr)
{  
  for (int i=0;i<TBFE_Base::ActorList.size();i++)
    {
      if (TBFE_Base::ActorList.at(i)==actorPtr)
      	{
	  return i;
	};
    };
  return -1;
};
Actor * GetActorByNum(int actorNum)
{
  if (actorNum<TBFE_Base::ActorList.size())
    {
      return TBFE_Base::ActorList.at(actorNum);
    };
  return NULL;
};

SDL_Surface * TBFE_Base::CheckSheets(string source)
{
  for (int i=0;i<TBFE_Base::AnimationSheets.size();i++)
    {
      if (TBFE_Base::AnimationSheets.at(i).Source==source)
	{
	  return TBFE_Base::AnimationSheets.at(i).Data;
	};
    };
  AnimationSheet sheet;
  sheet.Data=loadImage(source);
  if (sheet.Data==NULL)
    {
      return NULL;
    };
  sheet.Source=source;
  TBFE_Base::AnimationSheets.push_back(sheet);
  return sheet.Data;
};
void TBFE_Base::DeleteAnimationSheets()
{
  for (int i=0;i<TBFE_Base::AnimationSheets.size();i++)
    {
      if (TBFE_Base::AnimationSheets.at(i).Data!=NULL)
	{
	  SDL_FreeSurface(TBFE_Base::AnimationSheets.at(i).Data);
	};
    };
  TBFE_Base::AnimationSheets.resize(0);
};
