#ifndef RenderableFactory_L
#define RenderableFactory_L
#include "tbfe/raster/Renderable.h"
template <class T:public Renderable>
class RenderableFactory
{
 private:
 public:
  Renderable * FromSource(std::string source)=0;
};
#endif
