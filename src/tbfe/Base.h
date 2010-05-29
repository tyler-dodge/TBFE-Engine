#ifndef TBFE_Base_L
#define TBFE_Base_L
#include <vector>
#include "actor/Actor.h"
#include "UI/Window.h"
#include "Console.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "map/Map.h"
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
  extern void DeleteTempSheets();
  extern int GetActorNum(Actor *);
  extern Actor * GetActorByNum(int);
  extern ModelData * CheckModels(string);
  extern SDL_Surface * CheckSheets(string);
  extern string GetSheetName(SDL_Surface *);
  extern GLuint GetTexture(SDL_Surface *);
  extern TTF_Font * GetFont();
  extern void SetFont(TTF_Font *);
  extern bool showCollision;
  extern SDL_Surface * GetCollisionTile();
  extern void SetCollisionTile(SDL_Surface *);
  extern Actor * GetMainPlayer();
  extern void SetMainPlayer(Actor *);
  extern Element * GetKeyTarget();
  extern void SetKeyTarget(Element *);
  extern Window * getWindowByNum(int);
  extern int getWindowNum(Window *);
  
  extern Quaternion getCameraAngle();
  extern void setCameraAngle(Quaternion);
  extern void rotateCamera(Quaternion);
  
  extern PositionF getCameraFollowOffset();
  extern void setCameraFollowOffset(float,float,float);

  extern PositionF getCameraOffset();
  extern void setCameraFollowOffset(float,float,float);
};
#endif
