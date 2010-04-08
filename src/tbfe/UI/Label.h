#ifndef Label_L
#define Label_L
#include "Element.h"
class Label:public Element
{
 private:
  SDL_Surface * text_;
  SDL_Color textColor_;
  string currentText_;
 public:
  SDL_Surface * renderElement();
  Label(int,int,string);
  ~Label();
  void reload();
};
#endif
