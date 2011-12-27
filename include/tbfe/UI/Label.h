#ifndef Label_L
#define Label_L
#include <boost/python.hpp>
#include "tbfe/UI/Element.h"
#include "tbfe/misc/TFont.h"
#define LABEL_TEXT "text"
class Label:public Element
{
 private:
  SDL_Surface * text_;
  SDL_Color textColor_;
  string currentText_;
  TFont * font_;
 public:
  SDL_Surface * renderElement();
  Label(int,int,string, TFont *);
  ~Label();
  void reload();
};
#endif
