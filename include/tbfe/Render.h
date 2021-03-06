#ifndef TBFE_Render_L
#define TBFE_Render_L
#include "tbfe/misc/Timer.h"
#include "tbfe/misc/Position.h"
#include "tbfe/map/Map.h"
#include <SDL/SDL_opengl.h>
#include "tbfe/raster/ScreenImage.h"
#include "tbfe/raster/RenderPipeline.h"
#include <vector>
class TBFE_Render
{
 private: 
  PositionI offset_;
  void renderActors();
  void renderWindowList();
  int renderMapLayer(int,int,int);
  void renderForeground(int,int,bool);
  GLfloat lightPosition_[4];
  PositionI dimensions_;
 public:
  void refreshMapLayer(int);
  TBFE_Render(int,int);
  ~TBFE_Render();
  void initializeTileSets(Map *);
  bool addTileSet(string);
  void init();
  void initGl();
  void setLightPosition(float,float,float);
  void finalRender(bool);
};
#endif
