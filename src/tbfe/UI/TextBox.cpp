#include "TextBox.h"
TextBox::TextBox(int x,int y,string text):Element(x,y)
{
  setProperty("text",nextSet(&text,'('));
  setProperty("scrollY","0");
  string xValue=nextSet(&text,';');
  setDimensions(TBFE_Base::MainConsole.evalExpression(xValue),TBFE_Base::MainConsole.evalExpression(nextSet(&text,')')));
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
      bool endLine=false;
      while (textSize<width && textPt<getProperty("text").size() && !endLine)
	{
	  int increase=0;
	  if (TBFE_Base::GetFont()!=NULL)
	    {
	      TTF_GlyphMetrics(TBFE_Base::GetFont(),getProperty("text")[textPt],NULL,NULL,NULL,NULL,&increase);
	    };
	  if (getProperty("text")[textPt]==(char)92 && getProperty("text")[textPt+1]=='n')
	    {
	      endLine=true;
	      textPt++;
	    }
	  else
	    {
	      textSize+=increase;
	      textSegment << getProperty("text")[textPt];
	    };
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
  int scrollY=atoi(getProperty("scrollY").c_str());
  bool lastLine=false;
  SDL_Rect textDimensions;
  if (scrollY<0)
    {
      scrollY=0;
    };
  for (int i=scrollY/text_.at(0)->h;i<text_.size();i++)
    {
      if (lastLine)
	{
	  return;
	};
      textDimensions.x=0;
      textDimensions.y=0;
      textDimensions.w=text_.at(i)->w;
      textDimensions.h=text_.at(i)->h;
      if (scrollY/text_.at(0)->h==i)
	{
	  textDimensions.y=scrollY-(scrollY/text_.at(0)->h)*text_.at(0)->h;
	};
      if (text_.at(i)->h*i-scrollY>getDimensions().Y)
	{
	  lastLine=true;
	  textDimensions.h=text_.at(i)->h*i-scrollY-getDimensions().Y;
	  if (textDimensions.h<0)
	    {
	      return;
	    };
	};
      applyImage(ScreenPosition.X+CurrentPosition.X,ScreenPosition.Y+CurrentPosition.Y+text_.at(i)->h*i,text_.at(i),screen,&textDimensions);
    };
};
