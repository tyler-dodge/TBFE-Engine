#ifndef TBFE_Render_L
#define TBFE_Render_L

#include <boost/python.hpp>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_opengl.h"
#include "tbfe/misc/Timer.h"
#include "tbfe/misc/SdlFunctions.h"
//#include "SunVector.h"
#include "tbfe/UI/Window.h"
#include "tbfe/Base.h"
#include "tbfe/actor/Actor.h"
#include "tbfe/Base.h"
#include <vector>
class TBFE_Render
{
 private: 
  Position offset_;
  vector<TileSheet> tileSet_;
  void renderActors();
  void renderWindowList();
  int renderMapLayer(int,int,int);
  void renderForeground(int,int,bool);
  GLfloat lightPosition_[4];
  MeshData map_;
 public:
  void refreshMapLayer(int);
  TBFE_Render();
  ~TBFE_Render();
  void initializeTileSets();
  bool addTileSet(string);
  void init();
  void initGl();
  void setLightPosition(float,float,float);
  void finalRender(bool);
};
#endif
