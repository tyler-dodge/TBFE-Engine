#ifndef TBFE_Base_L
#define TBFE_Base_L
#include <vector>
#include "actor/Actor.h"
#include "UI/Window.h"
#include "Console.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
namespace TBFE_Base
{
  extern vector<Actor *> ActorList;
  extern vector<Window *> WindowList;
  extern Console MainConsole;
  extern int TileSize;
  extern int NumberOfActors;  
  extern bool KeyControl;
  extern Map CurrentMap;
  extern int Time;
  extern float GameSpeed;
  extern Position ScreenDimensions;
  extern void DeleteAnimationSheets();
  extern int GetActorNum(Actor *);
  extern Actor * GetActorByNum(int);
  extern SDL_Surface * CheckSheets(string);
  
  extern TTF_Font * GetFont();
  extern void SetFont(TTF_Font *);

  extern SDL_Surface * GetCollisionTile();
  extern void SetCollisionTile(SDL_Surface *);
  extern Actor * GetMainPlayer();
  extern void SetMainPlayer(Actor *);
}
#endif
