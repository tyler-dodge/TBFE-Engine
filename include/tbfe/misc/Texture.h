#ifndef Texture_L
#define Texture_L
#include<boost/python.hpp>
#include<string>
class Texture
{
 private:
  GLuint texture;
 public:
  static DirectoryFactory<Texture> * getFactory();
  Texture(string name);
  ~Texture();
  void apply();
  
};
#endif
