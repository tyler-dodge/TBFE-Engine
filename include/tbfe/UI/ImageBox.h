#ifndef ImageBox_L
#define ImageBox_L
#include <boost/python.hpp>
#include <iostream>
#include "tbfe/UI/Element.h"
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
