#include "tbfe/raster/RenderPipeline.h"
RenderPipeline::RenderPipeline()
{
}
void RenderPipeline::add(Renderable * renderable)
{
  data[renderable->getParams()].push_back(renderable);
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
