#ifndef RenderPipeline_L
#define RenderPipeline_L
#include "tbfe/raster/Renderable.h"
class RenderPipeline
{
 private:
  std::vector<Renderable> list;
 public:
  RenderPipeline();
  void add(Renderable);
  void run();
};
#endif
