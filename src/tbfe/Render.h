#ifndef TBFE_Render_L
#define TBFE_Render_L

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "misc/Timer.h"
#include "misc/SdlFunctions.h"
//#include "SunVector.h"
#include "UI/Window.h"
#include "Base.h"
#include "actor/Actor.h"
#include "Base.h"
#include <vector>
class TBFE_Render
{
 private: 
  SDL_Surface *collision_;
  SDL_Surface *window_;
  int lightingPercentage_;
  SDL_Surface *darkness_;
  SDL_Color textColor_;
  Position offset_;
  SDL_Surface * screen_;
  vector<SDL_Surface *> tileSet_;
  void renderActors();
  void arrangeActors();
  void renderWindowList();
  int renderMapLayer(int,int,int);
  void renderForeground(int,int,bool);
 public:
  TBFE_Render();
  ~TBFE_Render();
  void initializeTileSets();
  bool addTileSet(string);
  void changeLighting(int);
  void init();
  void finalRender(bool);
};
#endif
