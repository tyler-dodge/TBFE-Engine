#include "tbfe/raster/ScreenImageRenderParams.h"
void ScreenImageRenderParams::setUp(int screenX, int screenY)
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,screenX,screenY,0,1,10);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_TEXTURE_2D);
  glDepthFunc(GL_ALWAYS);
  glDisable(GL_LIGHTING);
}
void ScreenImageRenderParams::setPosition(int x,int y)
{
  x_=x;
  y_=y;
}
void ScreenImageRenderParams::setUpInstance()
{
  glPushMatrix();
  glTranslatef(x_,y_,-2);
}
void ScreenImageRenderParams::tearDownInstance()
{
  glPopMatrix();
}
void ScreenImageRenderParams::tearDown()
{  
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glDepthFunc(GL_LEQUAL);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}
int ScreenImageRenderParams::hashCode()
{
  return IMAGE_RENDER_HASH_CODE;
}
