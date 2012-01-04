#ifndef ScreenImage_L
#define ScreenImage_L
#include "tbfe/raster/Renderable.h"
#include "tbfe/raster/ScreenImageRenderParams.h"
#define GET_SCREEN_IMAGE(fileName) ScreenImage::getFactory()->FromFileName((fileName))
class ScreenImage : public Renderable
{
 private:
  PositionI position;
  PositionI dimensions;
  ScreenImage(std::string source);
  ScreenImageRenderParams params;
  static DirectoryFactory<ScreenImage> factory;
  static ScreenImage Create(std::string);
  static void Destroy(ScreenImage * t);
  Texture texture;
  bool isNull_;
 public:
  ScreenImage();
  static DirectoryFactory<ScreenImage> * getFactory();
  bool isNull();
  RenderParameters * getParams();
  void draw();
  void setPosition(int x,int y);
  PositionI getPosition();
  void setDimensions(int x,int y);
  PositionI getDimensions();
};
#endif
