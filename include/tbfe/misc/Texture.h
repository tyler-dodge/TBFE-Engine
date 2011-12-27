#ifndef Texture_L
#define Texture_L
#include "SDL/SDL_opengl.h"
#include<string>
#include "tbfe/misc/DirectoryFactory.h"
class Texture
{
 private:
  GLuint texture;
  class TextureFactory;
  static TextureFactory factory;
  Texture(std::string name);
  bool isValid;
 public:
  static DirectoryFactory<Texture> * getFactory();
  void apply();
  
};
#endif
