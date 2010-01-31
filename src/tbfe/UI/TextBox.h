#ifndef TextBox_L
#define TextBox_L
#include "Element.h"
namespace UI
{
  class TextBox:public Element
  {
  private:
    SDL_Surface * text_;
    SDL_Color textColor_;
    bool isSelected_;
  public:
    void renderElement(SDL_Surface *, Position);
    Label(int,int,string);
    ~Label();
    void reload();
  };
};
#endif
