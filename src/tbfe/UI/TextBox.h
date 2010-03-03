#ifndef TextBox_L
#define TextBox_L
#include "Element.h"
class TextBox:public Element
{
 private:
  vector<SDL_Surface *> text_;
  SDL_Color textColor_;
  void wordWrap();
  SDL_Surface * intermediary_;
  int currentScrollY;
  bool isReloaded;
 public:
  SDL_Surface * renderElement();
  TextBox(int,int,string);
  ~TextBox();
  void reload();
};
#endif
