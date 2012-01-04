#include "tbfe/raster/ScreenImageRenderParams.h"
void ScreenImageRenderParams::setUp()
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  PositionI screenDimensions;
  glOrtho(0,screenDimensions.X,screenDimensions.Y,0,1,10);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_TEXTURE_2D);
  glDepthFunc(GL_ALWAYS);
  glDisable(GL_LIGHTING);
}
void ScreenImageRenderParams::setUpInstance()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(x,y,-2);
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
