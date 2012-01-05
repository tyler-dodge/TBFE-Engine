#ifndef RenderPipeline_L
#define RenderPipeline_L
#include<list>
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
  typedef std::list<Renderable *> rList;
  typedef std::map<RenderParameters *, rList, ParamsComparator > RenderMap;
  typedef std::pair<rList *,rList::iterator> Id_Item;
  typedef std::map<Identifier *,Id_Item> IdMap;
  IdMap ids;
  RenderMap data;
 public:
  RenderPipeline();
  void add(Identifier *,Renderable *);
  void remove(Identifier *);
  void run(int screenX, int screenY);
};
#endif
