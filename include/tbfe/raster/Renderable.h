#ifndef Renderable_L
#define Renderable_L
#include "tbfe/raster/RenderParameters.h"
class Renderable
{
 private:
 public:
  virtual RenderParameters * getParams()=0;
  virtual void draw()=0;
};
#endif
