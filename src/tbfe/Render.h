#ifndef TBFE_Render_L
#define TBFE_Render_L

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_opengl.h"
#include "misc/Timer.h"
#include "misc/SdlFunctions.h"
#include <assimp.hpp>
#include <assimp.h>
#include <aiScene.h>
#include <aiPostProcess.h>
//#include "SunVector.h"
#include "UI/Window.h"
#include "Base.h"
#include "actor/Actor.h"
#include "Base.h"
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
