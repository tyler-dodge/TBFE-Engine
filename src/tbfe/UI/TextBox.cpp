#include "TextBox.h"
TextBox::TextBox(int x,int y,string text):Element(x,y)
{
  setProperty("text",nextSet(&text,'('));
  setProperty("scrollY","0");
  setProperty("border","1");
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
	  else if (getProperty("text")[textPt]=='\n')
	    {
	      endLine=true;
	    }
	  else
	    {
	      textSize+=increase;
	      textSegment << getProperty("text")[textPt];
	    };
	  textPt++;
	};
      if (textSegment.str()=="")
	{
	  textSegment << " ";
	};
      text_.push_back(TTF_RenderText_Blended(TBFE_Base::GetFont(),textSegment.str().c_str(),textColor_));
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
  SDL_Surface * intermediary = SDL_CreateRGBSurface(0, getDimensions().X, getDimensions().Y, 32, 
						    0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  for (int i=scrollY/text_.at(0)->h;i<text_.size();i++)
    {
      if (lastLine)
	{
	  applyImage(ScreenPosition.X+CurrentPosition.X,ScreenPosition.Y+CurrentPosition.Y,intermediary,NULL);
	};
      textDimensions.x=0;
      textDimensions.y=0;
      textDimensions.w=text_.at(i)->w;
      textDimensions.h=text_.at(i)->h;
      if (scrollY/text_.at(0)->h==i)
	{
	  textDimensions.y=scrollY-(scrollY/text_.at(0)->h)*text_.at(0)->h;
	};
      if (text_.at(i)->h*(i+1)-scrollY>getDimensions().Y)
	{
	  lastLine=true;
	  textDimensions.h+=getDimensions().Y-(text_.at(i)->h*(i+1)-scrollY);
	  if (textDimensions.h<0)
	    {
	      return;
	    };
	};
      SDL_Rect position;
      position.x=0;
      position.y=text_.at(i)->h*i-scrollY;
      cout << position.y << "\n";
      SDL_BlitSurface(text_.at(i),NULL,intermediary,&position);
    };
};
