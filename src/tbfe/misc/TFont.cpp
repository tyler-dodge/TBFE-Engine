#include "tbfe/misc/TFont.h"

SDL_Surface * TFont::render_text(std::string text)
{
  SDL_Color color;
  return TTF_RenderText_Blended(font_,text.c_str(),color);
}
int TFont::get_char_height(char letter)
{
  int height;
  TTF_GlyphMetrics(font_,letter,
		   NULL,NULL,NULL,NULL,&height);
  return height;
}
