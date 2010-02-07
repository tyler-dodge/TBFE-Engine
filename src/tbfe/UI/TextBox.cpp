#include "TextBox.h"
TextBox::TextBox(int x,int y,string text):Element(x,y)
{
  setProperty("text",nextSet(&text,'('));
  string xValue=nextSet(&text,';');
  setDimensions(atoi(xValue.c_str()),atoi(nextSet(&text,')').c_str()));
  textColor_.r=255;
  textColor_.g=255;
  textColor_.b=255;
  wordWrap();
};
void TextBox::wordWrap()
{
  if (SDL_WasInit(SDL_INIT_VIDEO)==0)
    {
      SDL_Init(SDL_INIT_VIDEO);
    };
  int width=getDimensions().X;
  for (int i=0;i<text_.size();i++)
    {
      SDL_FreeSurface(text_.at(i));
    };
  text_.resize(0);
  
  int textPt=0;
  while (textPt<getProperty("text").size())
    {
      stringstream textSegment;
      int textSize=0;
      while (textSize<width && textPt<getProperty("text").size())
	{
	  int increase=0;
	  if (TBFE_Base::GetFont()!=NULL)
	    {
	      TTF_GlyphMetrics(TBFE_Base::GetFont(),getProperty("text")[textPt],NULL,NULL,NULL,NULL,&increase);
	    };
	  textSize+=increase;
	  textSegment << getProperty("text")[textPt];	
	  textPt++;
	};
      text_.push_back(TTF_RenderText_Solid(TBFE_Base::GetFont(),textSegment.str().c_str(),textColor_));
    };
};
TextBox::~TextBox()
{
  for (int i=0;i<text_.size();i++)
    {
      SDL_FreeSurface(text_.at(i));
    };
  text_.resize(0);
 
};
void TextBox::reload()
{
  wordWrap();
};
void TextBox::renderElement(SDL_Surface * screen, Position ScreenPosition)
{
  Position CurrentPosition=getPosition();
  for (int i=0;i<text_.size();i++)
    {
      applyImage(ScreenPosition.X+CurrentPosition.X,ScreenPosition.Y+CurrentPosition.Y+text_.at(i)->h*i,text_.at(i),screen,NULL);
    };
};
