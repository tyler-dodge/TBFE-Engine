#ifndef ScreenImageRenderParams_L
#define ScreenImageRenderParams_L
#include "tbfe/misc/Texture.h"
class ScreenImageRenderParams : public RenderParameters
{
public:
  void setUp();
  void setUpInstance();
  void tearDownInstance();
  void tearDown();
};
#endif
