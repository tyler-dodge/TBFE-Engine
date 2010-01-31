#ifndef ImageBox_L
#define ImageBox_L
#include <iostream>
#include "Element.h"
class ImageBox:public Element
{
 private:
  SDL_Surface * image_;
 public:
  void renderElement(SDL_Surface *, Position);
  ImageBox(int,int,string);
  void reload();
  ~ImageBox();
};

#endif
