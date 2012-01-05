#ifndef ScreenImageRenderParams_L
#define ScreenImageRenderParams_L
#include "tbfe/misc/Texture.h"
#include "tbfe/raster/RenderParameters.h"
#define IMAGE_RENDER_HASH_CODE 57375153
class ScreenImageRenderParams : public RenderParameters
{
 private:
  int x_,y_;
public:
  void setPosition(int x,int y);
  int hashCode();
  void setUp(int screenX,int screenY);
  void setUpInstance();
  void tearDownInstance();
  void tearDown();
};
#endif
