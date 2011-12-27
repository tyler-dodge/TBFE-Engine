#include "tbfe/UI/Label.h"
Label::Label(int x,int y,string text,TFont * font):Element(x,y), font_(font)
{
  textColor_.r=255;
  textColor_.g=255;
  textColor_.b=255;
  setProperty(LABEL_TEXT,text);
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
  if (currentText_!=getProperty(LABEL_TEXT))
    {
      currentText_=getProperty(LABEL_TEXT);
      SDL_FreeSurface(text_);
      text_=font_->render_text(getProperty(LABEL_TEXT));
      if (text_!=NULL)
	{
	  setDimensions(text_->w,text_->h);
	}
      else
	{
	  setDimensions(0,15);
	};
      currentText_=getProperty(LABEL_TEXT);
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
	  SDL_SetAlpha(text_,0,0);
	  SDL_BlitSurface(text_,NULL,intermediary_,NULL);
	};
      if (getProperty("border")=="1")
	{
	  drawBorders();
	};
      setProperty("reload","1");
    };
  if (getProperty("width")!="")
    {
      if (getDimensions().X!=atoi(getProperty("width").c_str()))
	{
	  SDL_FreeSurface(intermediary_);
	  intermediary_=SDL_DisplayFormatAlpha(text_);
	  setDimensions(atoi(getProperty("width").c_str()),getDimensions().Y);
	  drawBorders();
	};
      setProperty("reload","1");
    };
};
SDL_Surface * Label::renderElement()
{
  reload();
  return intermediary_;
};
