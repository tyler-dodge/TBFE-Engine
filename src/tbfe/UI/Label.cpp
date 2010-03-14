#include "Label.h"
Label::Label(int x,int y,string text):Element(x,y)
{
  textColor_.r=255;
  textColor_.g=255;
  textColor_.b=255;
  setProperty("text",text);
  text_=TTF_RenderText_Blended(TBFE_Base::GetFont(),getProperty("text").c_str(),textColor_);
  intermediary_=NULL;
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
  if (currentText_!=getProperty("text"))
    {
      currentText_=getProperty("text");
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
      if (intermediary_!=NULL)
	{
	  SDL_FreeSurface(intermediary_);
	};
      if (text_==NULL)
	{
	  intermediary_=NULL;
	}
      else
	{
	  intermediary_=SDL_CreateRGBSurface(0, text_->w, text_->h, 32, 
					     0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	  SDL_BlitSurface(text_,NULL,intermediary_,NULL);
	};
    };
  if (getProperty("width")!="")
    {
      setDimensions(atoi(getProperty("width").c_str()),getDimensions().Y);
    };
};
SDL_Surface * Label::renderElement()
{
  reload();
  return intermediary_;
};
