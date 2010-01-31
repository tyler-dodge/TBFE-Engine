#include "Window.h"
void Window::addElement(Element *NewElement)
{
  elements_.push_back(NewElement);
};
Window::Window(int width, int height, int positionX, int positionY, string ImageSource)
{
  setVisibility(true);
  elements_.resize(0);
  setDimensions(width,height);
  setScreenPosition(positionX,positionY);
  setShowBackground(true);
};
Window::~Window()
{
};
Element * Window::selectElement(std::string Name)
{
  for (int i=0;i<elements_.size();i++)
    {
      if (elements_.at(i)->getName()==Name)
	{
	  return elements_.at(i);
	};
    };
  return NULL;
};
void Window::renderElements(SDL_Surface * screen)
{
  for(int i=0;i<elements_.size();i++)
    {
      if (elements_.at(i)!=NULL)
	{
	  if (elements_.at(i)->getVisibility()==true)
	    {
	      elements_.at(i)->renderElement(screen,getScreenPosition());
	    };
	};
    };
};
bool Window::getVisibility()
{
  return isVisible_;
};
void Window::setVisibility(bool newVisibility)
{
  isVisible_=newVisibility;
};
Position Window::getDimensions()
{
  return dimensions_;
}
void Window::setDimensions(int width,int height)
{
  dimensions_.X=width;
  dimensions_.Y=height;
};
Position Window::getScreenPosition()
{
  return screenPosition_;
};
void Window::setScreenPosition(int x,int y)
{
  screenPosition_.X=x;
  screenPosition_.Y=y;
};
bool Window::getShowBackground()
{
  return showBackground_;
};
void Window::setShowBackground(bool newShowBackground)
{
  showBackground_=newShowBackground;
};
