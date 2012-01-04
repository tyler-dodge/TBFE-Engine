#ifndef RenderPipeline_L
#define RenderPipeline_L
#include<vector>
#include<map>
#include "tbfe/raster/Renderable.h"
#include "tbfe/raster/RenderParameters.h"
class ParamsComparator
{
 public:
  bool operator() (RenderParameters *,RenderParameters *);
};
class RenderPipeline
{
 private:
  typedef std::map<RenderParameters *, std::vector<Renderable *>, ParamsComparator > RenderMap;
  RenderMap data;
 public:
  RenderPipeline();
  void add(Renderable *);
  void run();
};
#endif
