#ifndef TextBox_L
#define TextBox_L
#include "Element.h"
class TextBox:public Element
{
 private:
  vector<SDL_Surface *> text_;
  vector<string> textData_;
  SDL_Surface * box_;
  SDL_Color textColor_;
  void wordWrap();
  int currentScrollY;
  bool isReloaded;
 public:
  SDL_Surface * renderElement();
  TextBox(int,int,string);
  ~TextBox();
  void reload();
};
#endif
