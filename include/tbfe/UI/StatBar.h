#ifndef StatBar_L
#define StatBar_L
#include <boost/python.hpp>
#include "tbfe/misc/StringConversion.h"
#include "tbfe/UI/Element.h"
class StatBar:public Element
{
 private:
  SDL_Surface * statBarSurface_;
  SDL_Surface * statBarBack_;
  SDL_Rect bar_;
  SDL_Rect barDimensions_;
  SDL_Surface * intermediary_;
  float percentage_;
 public:
  SDL_Surface * renderElement();
  void reload();
  StatBar(int,int,string);
  ~StatBar();
};
#endif
