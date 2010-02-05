#include "TextBox.h"
TextBox::TextBox(int x,int y,string text):Element(x,y)
{
  setProperty("text",nextSet(&text,'('));
  setProperty("width",nextSet(&text,','));
  setProperty("height",nextSet(&text,')'));
  textColor_.r=255;
  textColor_.g=255;
  textColor_.b=255;
  text_=TTF_RenderText_Solid(TBFE_Base::GetFont(),getProperty("text").c_str(),textColor_);
  int width=atoi(getProperty("width").c_str());
  if (text_->w>width)
    {
      int textPt=0;
      for (int i=0;i<text_->w/width;i++)
	{
	  SDL_Surface * wordWrap;
	  stringstream textSegment;
	  int textSize=0;
	  while (textSize<width && textPt<getProperty("text").size())
	    {
	      int increase=0;
	      if (TBFE_Base::GetFont()!=NULL)
		{
		  TTF_GlyphMetrics(TBFE_Base::GetFont(),' ',NULL,NULL,NULL,NULL,&increase);
		};
	      textSize+=increase;
	      textSegment << getProperty("text")[textPt];	
	      textPt++;
	    };
	  wordWrap=TTF_RenderText_Solid(TBFE_Base::GetFont(),textSegment.str().c_str(),textColor_);
	  applyImage(0,wordWrap->h*i,wordWrap,text_);
	  SDL_FreeSurface(wordWrap);
	};
    };
  setDimensions(atoi(getProperty("width").c_str()),atoi(getProperty("height").c_str()));
};
TextBox::~TextBox()
{
  SDL_FreeSurface(text_);
};
void TextBox::reload()
{
  SDL_FreeSurface(text_);
  text_=TTF_RenderText_Solid(TBFE_Base::GetFont(),getProperty("text").c_str(),textColor_);
};
void TextBox::renderElement(SDL_Surface * screen, Position ScreenPosition)
{
  Position CurrentPosition=getPosition();
  applyImage(ScreenPosition.X+CurrentPosition.X,ScreenPosition.Y+CurrentPosition.Y,text_,screen,NULL);
};
