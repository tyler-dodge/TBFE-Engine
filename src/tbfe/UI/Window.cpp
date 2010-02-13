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
  if (border_==NULL)
    {
      border_=TBFE_Base::CheckSheets("border.png");
    };
};
Window::~Window()
{
};
SDL_Surface * Window::border_=NULL;
Element * Window::getElement(std::string Name)
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
	  if (elements_.at(i)->getProperty("border")=="1")
	    {
	      Position elementDimensions=elements_.at(i)->getDimensions();
	      Position elementPosition=elements_.at(i)->getPosition();
	      if (border_!=NULL)
		{
		  for (int x=-2;x<elementDimensions.X+2;x+=border_->w)
		    {
		      SDL_Rect rect;
		      rect.x=0;
		      rect.y=0;
		      if (elementDimensions.X+2-x<border_->w)
			{
			  rect.w=elementDimensions.X+2-x;
			}
		      else
			{
			  rect.w=border_->w;
			};
		      rect.h=1;
		      //if (elementDimensions.Y-y<border_->h)
		      //	{
		      //	  rect.h=elementDimensions.Y-y;
		      //	}
		      //else
		      //	{
		      //	  rect.h=border_->h;
		      //	};
		      applyImage(screenPosition_.X+elementPosition.X+x,screenPosition_.Y+elementPosition.Y-2,border_,screen,&rect);
		      applyImage(screenPosition_.X+elementPosition.X+x,screenPosition_.Y+elementPosition.Y+elementDimensions.Y+2,border_,screen,&rect);
		    };
		  for (int y=-2;y<elementDimensions.Y+2;y+=border_->h)
		    {
		      SDL_Rect rect;
		      rect.x=0;
		      rect.y=0;
		      if (elementDimensions.Y+2-y<border_->h)
			{
			  rect.h=elementDimensions.Y+2-y;
			}
		      else
			{
			  rect.h=border_->h;
			};
		      rect.w=1;
		      applyImage(screenPosition_.X+elementPosition.X-2,screenPosition_.Y+elementPosition.Y+y,border_,screen,&rect);
		      applyImage(screenPosition_.X+elementPosition.X+elementDimensions.X+2,screenPosition_.Y+elementPosition.Y+y,border_,screen,&rect);
		    };
		};
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
