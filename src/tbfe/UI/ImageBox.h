#ifndef ImageBox_L
#define ImageBox_L
#include <iostream>
#include "Element.h"
class ImageBox:public Element
{
 private:
  SDL_Surface * image_;
 public:
  SDL_Surface * renderElement();
  ImageBox(int,int,string);
  void reload();
  ~ImageBox();
};

#endif
