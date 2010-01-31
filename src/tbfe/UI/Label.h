#ifndef Label_L
#define Label_L
#include "Element.h"
class Label:public Element
{
 private:
  SDL_Surface * text_;
  SDL_Color textColor_;
 public:
  void renderElement(SDL_Surface *, Position);
  Label(int,int,string);
  ~Label();
  void reload();
};
#endif
