#include "Element.h"
Element::Element(int x,int y)
{
  setVisibility(true);
  setPosition(x,y);
  background_=NULL;
};
Element::~Element()
{
};
SDL_Surface * Element::getBackground()
{
  return background_;
};
void Element::setBackground(string newBackground)
{
  background_=TBFE_Base::CheckSheets(newBackground);
};
Position Element::getPosition()
{
  return currentPosition_;
};
void Element::setPosition(int x,int y)
{
  currentPosition_.X=x;
  currentPosition_.Y=y;
};
Position Element::getDimensions()
{
  return dimensions_;
};
void Element::setDimensions(int width,int height)
{
  dimensions_.X=width;
  dimensions_.Y=height;
};
string Element::getName()
{
  return name_;
};
void Element::setName(string newName)
{
  name_=newName;
};
bool Element::getVisibility()
{
  return isVisible_;
};
void Element::setVisibility(bool newVisibility)
{
  isVisible_=newVisibility;
};
string Element::getProperty(string propertyName)
{
  for (int i=0;i<propertyList_.size();i++)
    {
      if (propertyList_.at(i).Name==propertyName)
	{
	  return propertyList_.at(i).Value;
	};
    };
  return "";
};
void Element::setProperty(string propertyName,string newValue)
{
  for (int i=0;i<propertyList_.size();i++)
    {
      if (propertyList_.at(i).Name==propertyName)
	{
	  propertyList_.at(i).Value=newValue;
	  return;
	};
    };
  Property newProperty;
  newProperty.Name=propertyName;
  newProperty.Value=newValue;
  propertyList_.push_back(newProperty);
};
void Element::drawBorders()
{  
  SDL_Surface * border = SDL_CreateRGBSurface(0, dimensions_.X+2,dimensions_.Y+2, 32, 
					      0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
  SDL_FillRect(border,NULL,0xffffffff);
  SDL_Rect rect;					
  rect.x=1;
  rect.y=1;
  rect.w=dimensions_.X;
  rect.h=dimensions_.Y;
  SDL_FillRect(border,&rect,0xff000000);
  if (intermediary_!=NULL)
    {      
      SDL_BlitSurface(intermediary_,NULL,border,&rect);
    };
  SDL_FreeSurface(intermediary_);
  intermediary_=border;
};
