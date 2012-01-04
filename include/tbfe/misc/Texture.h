#ifndef Texture_L
#define Texture_L
#define GET_TEXTURE(fileName) (Texture::getFactory()->FromFileName(fileName))
#include "SDL/SDL_opengl.h"
#include<string>
#include "tbfe/misc/DirectoryFactory.h"
#include "tbfe/misc/Position.h"
class Texture
{
 private:
  GLuint texture;
  static DirectoryFactory<Texture> factory;
  static Texture Create(std::string);
  static void Destroy(Texture * t);
  Texture(std::string name);
  bool isValid;
  PositionI dimensions;
  bool isArgb_;
 public:
  Texture();
  bool isNull();
  bool isArgb();
  static DirectoryFactory<Texture> * getFactory();
  void apply();
  PositionI getDimensions();
};
#endif
