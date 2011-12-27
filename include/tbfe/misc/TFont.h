class TFont;
#ifndef TFont_L
#define TFont_L
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<string>
class TFont
{
 private:
  TTF_Font * font_;
 public:
  SDL_Surface * render_text(std::string text);
  int get_char_height(char letter);
};
#endif
