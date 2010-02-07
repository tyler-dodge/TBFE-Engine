#ifndef TextBox_L
#define TextBox_L
#include "Element.h"
class TextBox:public Element
{
 private:
  vector<SDL_Surface *> text_;
  SDL_Color textColor_;
  void wordWrap();
 public:
  void renderElement(SDL_Surface *, Position);
  TextBox(int,int,string);
  ~TextBox();
  void reload();
};
#endif
