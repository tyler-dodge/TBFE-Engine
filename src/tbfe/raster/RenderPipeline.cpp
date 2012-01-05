#include "tbfe/raster/RenderPipeline.h"
RenderPipeline::RenderPipeline()
{
}
void RenderPipeline::add(Identifier * id,Renderable * renderable)
{
  rList * l = &(data[renderable->getParams()]);
  IdMap::iterator it=ids.find(id);
  if (it==ids.end())
    {
      l->push_back(renderable);
      ids[id]=(Id_Item(l,--l->end()));
    }
  else
    {
      *(it->second.second)=renderable;
    }
}
void RenderPipeline::remove(Identifier * id)
{
  IdMap::iterator it=ids.find(id);
  if (it!=ids.end())
    {
      it->second.first->erase(it->second.second);
    }
}
void RenderPipeline::run(int screenX, int screenY)
{
  RenderMap::iterator it;
  for (it=data.begin(); it!=data.end();it++)
    {
      it->first->setUp(screenX,screenY);
      rList::iterator rIt;
      for (rIt=it->second.begin();rIt!=it->second.end();rIt++)
	{
	  RenderParameters * params=(*rIt)->getParams();
	  params->setUpInstance();
	  (*rIt)->draw();
	  params->tearDownInstance();
	}
      it->first->tearDown();
    }
}
bool ParamsComparator::operator()(RenderParameters * A,RenderParameters * B)
{
  return A->hashCode()==B->hashCode();
}
