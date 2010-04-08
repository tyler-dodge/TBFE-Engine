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
  intermediary_=NULL;
  wordWrap();
};
void TextBox::wordWrap()
{
  if (SDL_WasInit(SDL_INIT_VIDEO)==0)
    {
      SDL_Init(SDL_INIT_VIDEO);
    };
  int width=getDimensions().X;
  int textPt=0;
  int lineNum=0;
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
      bool reloadLine=false;
      if (lineNum==textData_.size())
	{
	  reloadLine=true;
	  textData_.push_back(textSegment.str());
	  text_.push_back(NULL);
	}
      else if (lineNum>textData_.size())
	{
	  return;
	}
      else if (textData_.at(lineNum)!=textSegment.str())
	{
	  reloadLine=true;
	  textData_.at(lineNum)=textSegment.str();
	  if (text_.at(lineNum)!=NULL)
	    {
	      SDL_FreeSurface(text_.at(lineNum));
	    };
	};
      if (reloadLine)
	{
	  SDL_Surface * text=TTF_RenderText_Blended(TBFE_Base::GetFont(),textSegment.str().c_str(),textColor_);
	  text_.at(lineNum)=SDL_DisplayFormatAlpha(text);
	  SDL_FreeSurface(text);
	};
      lineNum++;
    };
};
TextBox::~TextBox()
{
  for (int i=0;i<text_.size();i++)
    {
      SDL_FreeSurface(text_.at(i));
    };
  if (intermediary_!=NULL)
    {
      SDL_FreeSurface(intermediary_);
    };
  text_.resize(0);
 
};
void TextBox::reload()
{
  wordWrap();
  isReloaded=true;
  setProperty("reload","1");
};
SDL_Surface * TextBox::renderElement()
{
  Position CurrentPosition=getPosition();
  int scrollY=atoi(getProperty("scrollY").c_str());
  if (isReloaded==true || currentScrollY!=scrollY)
    {
      isReloaded=false;
      currentScrollY=scrollY;
      bool lastLine=false;
      SDL_Rect textDimensions;
      if (scrollY<0)
	{
	  scrollY=0;
	};
      if (intermediary_!=NULL)
	{
	  SDL_FreeSurface(intermediary_);
	};
      intermediary_ = SDL_CreateRGBSurface(0, getDimensions().X, getDimensions().Y, 32, 
					   0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
      SDL_FillRect(intermediary_,NULL,0xff000000);
      if (scrollY/text_.at(0)->h>=text_.size()-1)
	{
	  scrollY=text_.at(0)->h*(text_.size()-1);
	  stringstream newScroll;
	  newScroll << scrollY;
	  currentScrollY=scrollY;
	  setProperty("scrollY",newScroll.str());
	};
      for (int i=scrollY/text_.at(0)->h;i<text_.size();i++)
	{
	  if (lastLine)
	    {
	      if (getProperty("border")=="1")
		{
		  drawBorders();
		};
	      return intermediary_;
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
		  if (getProperty("border")=="1")
		    {
		      drawBorders();
		    };
		  return intermediary_;
		};
	    };
	  SDL_Rect position;
	  position.x=0;
	  position.y=text_.at(i)->h*i-scrollY;
	  SDL_BlitSurface(text_.at(i),NULL,intermediary_,&position);
	};
      
      if (getProperty("border")=="1")
	{
	  drawBorders();
	};
    };
  return intermediary_;
};
