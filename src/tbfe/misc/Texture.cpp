#include "tbfe/misc/Texture.h"
#include<vector>
#include<map>
#include "tbfe/misc/SdlFunctions.h"
DirectoryFactory<Texture> Texture::factory(Create,Destroy);
Texture::Texture(std::string name)
{
  SDL_Surface * image=loadImage(name);
  if (image)
    {
      texture=bindImage(image);
      isArgb_=image->format->BytesPerPixel==4;
      SDL_FreeSurface(image);
      isValid=true;
      dimensions=PositionI(image->w,image->h,0);
    }
}
PositionI Texture::getDimensions()
{
  return dimensions;
}
Texture::Texture()
{
  isValid=false;
}
bool Texture::isNull()
{
  return !isValid;
}
DirectoryFactory<Texture> * Texture::getFactory()
{
  return &Texture::factory;
}
void Texture::apply()
{
  glBindTexture( GL_TEXTURE_2D, texture );
}
bool Texture::isArgb()
{
  return isArgb_;
}
Texture Texture::Create(std::string name)
{
  return Texture(name);
}

void Texture::Destroy(Texture * t)
{
  glDeleteTextures(1,&t->texture);
}
