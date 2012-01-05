#include "tbfe/raster/ScreenImage.h"
#include "tbfe/Console.h"
#include <sstream>
ScreenImage::ScreenImage()
{
}
ScreenImage::ScreenImage(std::string source) : texture(GET_TEXTURE(source))
{
  dimensions=texture.getDimensions();
}
DirectoryFactory<ScreenImage> * ScreenImage::getFactory()
{
  return &factory;
}
bool ScreenImage::isNull()
{
  return isNull_;

}
RenderParameters * ScreenImage::getParams()
{
  params.setPosition(position.X,position.Y);
  return &params;
}
void ScreenImage::draw()
{
  if (texture.isArgb())
    {
      glEnable(GL_BLEND);
      glEnable(GL_ALPHA_TEST);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      glAlphaFunc(GL_GREATER,0.1f);
      glColor4f(1.0f,1.0f,1.0f,1.0f);
    }
  else
    {
      glDisable(GL_BLEND);
      glDisable(GL_ALPHA_TEST);
    }
  texture.apply();
  PositionI start(0,0,0);
  PositionI end(1,1,0);
  glBegin(GL_QUADS);
  glTexCoord2f(start.X,start.Y);glVertex3f(0,0,0);
  glTexCoord2f(start.X,start.Y+end.Y);glVertex3f(0,dimensions.Y,0);
  glTexCoord2f(start.X+end.X,start.Y+end.Y);glVertex3f(dimensions.X,dimensions.Y,0);
  glTexCoord2f(start.X+end.X,start.Y);glVertex3f(dimensions.X,0,0);
  glEnd();
  std::stringstream test;
  test << position.X << "," << position.Y << "," << dimensions.X << "," << dimensions.Y << "\n";
  CONSOLE_WRITE(test.str());
}
void ScreenImage::setPosition(int x,int y)
{
  position=PositionI(x,y,0);
}
DirectoryFactory<ScreenImage> ScreenImage::factory(Create,Destroy);
ScreenImage ScreenImage::Create(std::string name)
{
  return ScreenImage(name);
}
void ScreenImage::Destroy(ScreenImage * image)
{
}
void ScreenImage::setDimensions(int x,int y)
{
  dimensions.X=x;
  dimensions.Y=y;
}
PositionI ScreenImage::getDimensions()
{
  return dimensions;
}
