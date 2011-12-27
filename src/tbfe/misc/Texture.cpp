#include "tbfe/misc/Texture.h"
#include<vector>
#include<map>
#include "tbfe/misc/SdlFunctions.h"
class Texture::TextureFactory:public DirectoryFactory<Texture> 
{
private:
  std::map<std::string,Texture> textures;
  typedef std::pair<std::string,Texture> TexPair;
  typedef std::map<std::string,Texture>::iterator TexIt;
public:
  TextureFactory();
  ~TextureFactory();
  Texture FromFileName(std::string fileName);
};
Texture::TextureFactory::TextureFactory()
{
}
Texture::TextureFactory::~TextureFactory()
{
  map<std::string,Texture>::iterator it;

  for ( it=textures.begin() ; it != textures.end(); it++ )
    {
      glDeleteTextures( 1, &(it->second.texture) );
    }
}
Texture Texture::TextureFactory::FromFileName(std::string fileName)
{
  TexIt it=textures.find(fileName);
  Texture * texture;
  if (it==textures.end())
    {
      texture=new Texture(fileName);
      if (texture->isValid)
	{
	  TexPair pair(*textures.insert(textures.begin(),TexPair(fileName,*texture)));
	  delete texture;
	  texture=&pair.second;
 	}
    }
  return *texture;
}
Texture::TextureFactory Texture::factory;
Texture::Texture(std::string name)
{
  SDL_Surface * image=loadImage(name);
  if (image)
    {
      texture=bindImage(image);
      SDL_FreeSurface(image);
      isValid=true;
    }
}
DirectoryFactory<Texture> * Texture::getFactory()
{
  return &Texture::factory;
}
void Texture::apply()
{
  glBindTexture( GL_TEXTURE_2D, texture );
}
