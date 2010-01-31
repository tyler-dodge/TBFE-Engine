class TBFE_Base;
#ifndef TBFE_Base_L
#define TBFE_Base_L
#include <vector>
#include "actor/Actor.h"
#include "UI/Window.h"
#include "Console.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
class TBFE_Base
{
 private:
  static vector<AnimationSheet> AnimationSheets;
 public:
  TBFE_Base();
  ~TBFE_Base();
  static SDL_Surface * CheckSheets(string);
  static Console MainConsole;
  static Actor * MainPlayer;
  static vector<Actor *> ActorList;
  static vector<Window *> WindowList;
  static int TileSize;
  static int NumberOfActors;  
  static bool KeyControl;
  static Map CurrentMap;
  static int Time;
  static Actor * Talker;
  static TTF_Font *font;
  static Element *KeyTarget;
  static float GameSpeed;
  static void DeleteAnimationSheets();
  static SDL_Surface * CollisionTile;
  static Position ScreenDimensions;
};
extern int GetActorNum(Actor *);
extern Actor * GetActorByNum(int);
#endif
