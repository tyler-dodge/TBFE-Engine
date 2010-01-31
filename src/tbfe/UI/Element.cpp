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
