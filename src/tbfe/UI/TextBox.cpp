#include "TextBox.h"
TextBox::TextBox(int x,int y,string text):Element_Base(x,y)
{
  textColor.r=255;
  textColor.g=255;
  textColor.b=255;
  Special=text;
  Text=TTF_RenderText_Solid(TBFE_Base::font,Special.c_str(),textColor);
  Special=text;
  Dimensions.X=Text->w;
  Dimensions.Y=Text->h;
};
TextBox::~TextBox()
{
  SDL_FreeSurface(Text);
};
void TextBox::Reload()
{
  SDL_FreeSurface(Text);
  Text=TTF_RenderText_Solid(TBFE_Base::font,Special.c_str(),textColor);
  Dimensions.X=Text->w;
  Dimensions.Y=Text->h;
};
void TextBox::RenderElement(SDL_Surface * screen, Position ScreenPosition)
{
  ApplyImage(ScreenPosition.X+CurrentPosition.X,ScreenPosition.Y+CurrentPosition.Y,Text,screen,NULL);
};
