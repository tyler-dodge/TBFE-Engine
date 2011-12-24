#ifndef Model_L
#define Model_L
#include "tbfe/raster/Renderable.h"
class Model
{
 public:
  
  RenderParameters * getParams()=0;
  void draw()=0;
};
#endif
