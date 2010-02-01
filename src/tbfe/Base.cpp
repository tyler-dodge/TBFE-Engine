#include "Base.h"
/* Private TBFE_Base
   extern vector<AnimationSheet> AnimationSheets;
   extern Actor * MainPlayer;
   extern Element *KeyTarget;
   extern Actor * Talker;
   extern TTF_Font *font;*/
namespace TBFE_Base
{
  SDL_Surface * CollisionTile=NULL;
  Console MainConsole;
  vector<Actor *> ActorList;
  vector<Window *> WindowList;
  Position ScreenDimensions;
  int TileSize=100;
  int NumberOfActors;  
  bool KeyControl;
  Map CurrentMap;
  int Time;
  Actor * Talker;
  Actor * MainPlayer=NULL;
  TTF_Font * font;
  Element * KeyTarget;
  float GameSpeed=1;
  vector<AnimationSheet> AnimationSheets;
  int GetActorNum(Actor *actorPtr)
  {  
    for (int i=0;i<ActorList.size();i++)
      {
	if (ActorList.at(i)==actorPtr)
	  {
	    return i;
	  };
      };
    return -1;
  };
  Actor * GetActorByNum(int actorNum)
  {
    if (actorNum<ActorList.size())
      {
	return ActorList.at(actorNum);
      };
    return NULL;
  };
  TTF_Font * GetFont()
  {
    return font;
  };
  void SetFont(TTF_Font * newFont)
  {
    font=newFont;
  };
  SDL_Surface * GetCollisionTile()
  {
    return CollisionTile;
  };
  void SetCollisionTile(SDL_Surface * newTile)
  {
    CollisionTile=newTile;
  };
  SDL_Surface * CheckSheets(string source)
  {
    for (int i=0;i<AnimationSheets.size();i++)
      {
	if (AnimationSheets.at(i).Source==source)
	  {
	    return AnimationSheets.at(i).Data;
	  };
      };
    AnimationSheet sheet;
    sheet.Data=loadImage(source);
    if (sheet.Data==NULL)
      {
	return NULL;
      };
    sheet.Source=source;
    AnimationSheets.push_back(sheet);
    return sheet.Data;
  };
  void DeleteAnimationSheets()
  {
    for (int i=0;i<AnimationSheets.size();i++)
      {
	if (AnimationSheets.at(i).Data!=NULL)
	  {
	    SDL_FreeSurface(AnimationSheets.at(i).Data);
	  };
      };
    AnimationSheets.resize(0);
  };
  Actor * GetMainPlayer()
  {
    return MainPlayer;
  };
  void SetMainPlayer(Actor * newMainPlayer)
  {
    if (newMainPlayer!=NULL)
      {
	MainPlayer=newMainPlayer;
      };
  };
};
