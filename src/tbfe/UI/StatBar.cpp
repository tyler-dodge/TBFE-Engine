#include "StatBar.h"
StatBar::StatBar(int x,int y,string newSpecial):Element(x,y)
{
  intermediary_=NULL;
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
  percentage_=(float)atoi(getProperty("percentage").c_str());
  SDL_BlitSurface(intermediary_,&barDimensions_,statBarBack_,NULL);
  bar_.x=0;
  bar_.y=0;
  bar_.w=percentage_/100*barDimensions_.w;
  bar_.h=15;
  SDL_Rect position;
  position.x=0;
  position.y=1;
  SDL_BlitSurface(intermediary_,&bar_,statBarSurface_,&position);
};
StatBar::~StatBar()
{
};
SDL_Surface * StatBar::renderElement()
{
  if (percentage_!=(float)atoi(getProperty("percentage").c_str()))
    {
      reload();
    };
  return intermediary_;
};
