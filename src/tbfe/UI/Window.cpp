#include "tbfe/UI/Window.h"
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
  image_=NULL;
  background_=NULL;
};
Window::~Window()
{
};
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
SDL_Surface * Window::renderElements()
{
  bool reload=false;
  for(int i=0;i<elements_.size();i++)
    {
      if (elements_.at(i)!=NULL)
	{
	  SDL_Surface * element=elements_.at(i)->renderElement();
	  if (element!=NULL)
	    {
	      if (elements_.at(i)->getProperty("reload")=="1")
		{
		  elements_.at(i)->setProperty("reload","0");
		  reload=true;
		};
	    };
	};
    };
  if (reload || image_==NULL)
    {
      bool reloadBackground=false;
      if (background_==NULL)
	{
	  reloadBackground=true;
	}
      else if (background_->w!=dimensions_.X || background_->h!=dimensions_.Y)
	{
	  if (background_!=NULL)
	    {
	      SDL_FreeSurface(background_);
	    };
	  reloadBackground=true;
	};
      if (reloadBackground)
	{
	  background_=SDL_CreateRGBSurface(0,dimensions_.X,dimensions_.Y,32,
					   0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
	  if (showBackground_)
	    {
	      SDL_FillRect(background_,NULL,0xff000000);
	    }
	  else
	    {
	      SDL_FillRect(background_,NULL,0x00000000);
	    };
	};
      if (image_!=NULL)
	{
	  SDL_FreeSurface(image_);
	};
      image_=SDL_DisplayFormatAlpha(background_);
      for (int i=0;i<elements_.size();i++)
	{
	  if (elements_.at(i)!=NULL)
	    {
	      Position elementPosition=elements_.at(i)->getPosition();
	      SDL_Rect rect;
	      rect.x=elementPosition.X;
	      rect.y=elementPosition.Y;
	      SDL_Surface * element=elements_.at(i)->renderElement();
	      if (element!=NULL)
		{
		  if (showBackground_)
		    {
		      SDL_SetAlpha(element,SDL_SRCALPHA,0);
		    }
		  else
		    {
		      SDL_SetAlpha(element,0,0);
		    };
		  SDL_BlitSurface(element,NULL,image_,&rect);
		};
	    };
	};
    };
  return image_;
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
