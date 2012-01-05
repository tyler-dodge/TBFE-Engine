#ifndef Renderable_L
#define Renderable_L
#include "tbfe/raster/RenderParameters.h"
#include "tbfe/misc/Identifier.h"
class Renderable
{
 public:
  virtual RenderParameters * getParams()=0;
  virtual void draw()=0;
};
#endif
