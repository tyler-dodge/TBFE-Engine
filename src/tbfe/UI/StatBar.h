#ifndef StatBar_L
#define StatBar_L
#include "Element.h"
class StatBar:public Element
{
 private:
  SDL_Surface * statBarSurface_;
  SDL_Surface * statBarBack_;
  SDL_Rect bar_;
  SDL_Rect barDimensions_;
  float percentage_;
 public:
  void renderElement(SDL_Surface *, Position);
  void reload();
  StatBar(int,int,string);
  ~StatBar();
};
#endif
