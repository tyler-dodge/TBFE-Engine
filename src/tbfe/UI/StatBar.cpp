#include "StatBar.h"
StatBar::StatBar(int x,int y,string newSpecial):Element(x,y)
{
  setSpecial(newSpecial);
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
  string checkSpecial=getSpecial();
  if (checkSpecial!="")
    {
      if (checkSpecial.find('(')!=string::npos)
	{
	  nextSet(&checkSpecial,'(');
	  setDimensions(atoi(nextSet(&checkSpecial,')').c_str()),statBarSurface_->h);
	};
    };
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
  SDL_FreeSurface(statBarSurface_);
  SDL_FreeSurface(statBarBack_);
};
void StatBar::renderElement(SDL_Surface * screen, Position ScreenPosition)
{
  percentage_=(float)atoi(getSpecial().c_str());
  Position CurrentPosition=getPosition();
  applyImage(ScreenPosition.X+CurrentPosition.X,ScreenPosition.Y+CurrentPosition.Y,statBarBack_,screen,&barDimensions_);
  bar_.x=0;
  bar_.y=0;
  bar_.w=percentage_/100*barDimensions_.w;
  bar_.h=15;
  applyImage(ScreenPosition.X+CurrentPosition.X,ScreenPosition.Y+CurrentPosition.Y+1,statBarSurface_,screen,&bar_);
};
