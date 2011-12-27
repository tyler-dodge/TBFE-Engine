#ifndef TextBox_L
#define TextBox_L
#include <boost/python.hpp>
#include "tbfe/UI/Element.h"
#include "tbfe/misc/StringConversion.h"
#include "tbfe/Console.h"
#include "tbfe/misc/TFont.h"
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
  TFont * font_;
 public:
  SDL_Surface * renderElement();
  TextBox(int,int,string,TFont *);
  ~TextBox();
  void reload();
};
#endif
