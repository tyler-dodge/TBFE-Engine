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
  border_=TBFE_Base::CheckSheets("border.png");
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
void Window::renderElements(SDL_Surface * screen)
{
  for(int i=0;i<elements_.size();i++)
    {
      if (elements_.at(i)!=NULL)
	{
	  SDL_Surface * element=elements_.at(i)->renderElement();
	  if (elements_.at(i)->getProperty("border")=="1")
	    {
	      Position elementDimensions=elements_.at(i)->getDimensions();
	      Position elementPosition=elements_.at(i)->getPosition();
	      SDL_Surface * border = SDL_CreateRGBSurface(0, elementDimensions.X+4,elementDimensions.Y+4, 32, 
							  0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	      if (border_!=NULL)
		{
		  for (int x=0;x<elementDimensions.X+4;x+=border_->w)
		    {
		      SDL_Rect rect;
		      rect.x=0;
		      rect.y=0;
		      if (elementDimensions.X+4-x<border_->w)
			{
			  rect.w=elementDimensions.X+4-x;
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
		      SDL_Rect pos;
		      pos.x=x;
		      pos.y=0;
		      SDL_BlitSurface(border_,&rect,border,&pos);

		      pos.x=x;
		      pos.y=elementDimensions.Y+3;
		      SDL_BlitSurface(border_,&rect,border,&pos);
		    };
		  for (int y=0;y<elementDimensions.Y+4;y+=border_->h)
		    {
		      SDL_Rect rect;
		      rect.x=0;
		      rect.y=0;
		      if (elementDimensions.Y+4-y<border_->h)
			{
			  rect.h=elementDimensions.Y+4-y;
			}
		      else
			{
			  rect.h=border_->h;
			};
		      rect.w=1;
		      SDL_Rect pos;
		      pos.x=0;
		      pos.y=y;
		      SDL_BlitSurface(border_,&rect,border,&pos);

		      pos.x=elementDimensions.X+3;
		      pos.y=y;
		      SDL_BlitSurface(border_,&rect,border,&pos);
		    };
		};
	      SDL_Rect pos;
	      pos.x=2;
	      pos.y=2;
	      SDL_BlitSurface(element,NULL,border,&pos);
	      if (elements_.at(i)->getVisibility()==true)
		{
		  applyImage(getScreenPosition().X+elements_.at(i)->getPosition().X,
			     getScreenPosition().Y+elements_.at(i)->getPosition().Y,border,NULL);
		  applyImage(getScreenPosition().X+elements_.at(i)->getPosition().X+2,
			     getScreenPosition().Y+elements_.at(i)->getPosition().Y+2,element,NULL);
		};
	      SDL_FreeSurface(border);
	    }     
	  else if (element!=NULL)
	    {
	      if (elements_.at(i)->getVisibility()==true)
		{
		  applyImage(getScreenPosition().X+elements_.at(i)->getPosition().X,
			     getScreenPosition().Y+elements_.at(i)->getPosition().Y,element,NULL);
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
