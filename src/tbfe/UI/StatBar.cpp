#include "StatBar.h"
StatBar::StatBar(int x,int y,string newSpecial):Element(x,y)
{
  statBarSurface_=TBFE_Base::CheckSheets("Images/UI/StatBar.png");
  statBarBack_=TBFE_Base::CheckSheets("Images/UI/StatBarBack.png");
  if (statBarSurface_!=NULL)
    {
      setDimensions(statBarSurface_->w,statBarSurface_->h);
    }
  else
    {
      setDimensions(0,0);
    };
  if (newSpecial!="")
    {
      if (newSpecial.find('(')!=string::npos)
	{
	  nextSet(&newSpecial,'(');

	  setDimensions(atoi(nextSet(&newSpecial,')').c_str()),statBarSurface_->h);
	};
    };
  setProperty("percentage","100");
  Position Dimensions=getDimensions();
  barDimensions_.x=0;
  barDimensions_.y=0;
  barDimensions_.w=Dimensions.X;
  barDimensions_.h=Dimensions.Y;
};
void StatBar::reload()
{
};
StatBar::~StatBar()
{
};
void StatBar::renderElement(SDL_Surface * screen, Position ScreenPosition)
{
  float percentage=(float)atoi(getProperty("percentage").c_str());
  Position CurrentPosition=getPosition();
  applyImage(ScreenPosition.X+CurrentPosition.X,ScreenPosition.Y+CurrentPosition.Y,statBarBack_,&barDimensions_);
  bar_.x=0;
  bar_.y=0;
  bar_.w=percentage/100*barDimensions_.w;
  bar_.h=15;
  applyImage(ScreenPosition.X+CurrentPosition.X,ScreenPosition.Y+CurrentPosition.Y+1,statBarSurface_,&bar_);
};
