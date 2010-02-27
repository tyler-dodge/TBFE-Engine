#include "Label.h"
Label::Label(int x,int y,string text):Element(x,y)
{
  textColor_.r=255;
  textColor_.g=255;
  textColor_.b=255;
  setProperty("text",text);
  text_=TTF_RenderText_Blended(TBFE_Base::GetFont(),getProperty("text").c_str(),textColor_);
  if (text_!=NULL)
    {
      setDimensions(text_->w,text_->h);
    }
  else
    {
      setDimensions(0,0);
    };
};
Label::~Label()
{
  SDL_FreeSurface(text_);
};
void Label::reload()
{
  SDL_FreeSurface(text_);
  text_=TTF_RenderText_Blended(TBFE_Base::GetFont(),getProperty("text").c_str(),textColor_);
  if (text_!=NULL)
    {
      setDimensions(text_->w,text_->h);
    }
  else
    {
      setDimensions(0,15);
    };
  currentText_=getProperty("text");
};
void Label::renderElement(SDL_Surface * screen, Position ScreenPosition)
{
  if (currentText_!=getProperty("text"))
    {
      reload();
    };
  if (getProperty("width")!="")
    {
      setDimensions(atoi(getProperty("width").c_str()),getDimensions().Y);
    };
  Position currentPosition=getPosition();
  SDL_Surface * intermediary = SDL_CreateRGBSurface(0, text_->w, text_->h, 32, 
						    0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  SDL_BlitSurface(text_,0,intermediary,0);
  applyImage(ScreenPosition.X+currentPosition.X,ScreenPosition.Y+currentPosition.Y,intermediary,NULL);
};
