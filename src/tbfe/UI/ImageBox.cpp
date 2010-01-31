#include "ImageBox.h"
ImageBox::ImageBox(int x,int y,string Source):Element(x,y)
{
  setSpecial(Source);
  string ImageSource=Source;
  if (ImageSource.find('(')<ImageSource.size())
    {
      ImageSource=ImageSource.substr(0,ImageSource.find('('));
    };
  image_=loadImage(ImageSource.c_str());
  if (image_!=NULL)
    {
      setDimensions(image_->w,image_->h);
    }
  else
    {
      setDimensions(0,0);
    };
};
ImageBox::~ImageBox()
{
  SDL_FreeSurface(image_);
};
void ImageBox::reload()
{
  string ImageSource=getSpecial();
  if (ImageSource.find('(')<ImageSource.size())
    {
      ImageSource=ImageSource.substr(0,ImageSource.find('('));
    }
  SDL_FreeSurface(image_);
  image_=TBFE_Base::CheckSheets(ImageSource.c_str());
};
void ImageBox::renderElement(SDL_Surface * screen, Position ScreenPosition)
{
  string Box;
  SDL_Rect Clip;
  string Special=getSpecial();
  if (Special.find('(')<Special.length())
    {
      string Data;
      int StringPos;
      Box=Special.substr(Special.find('(')+1);
      
      StringPos=(int)Box.find(';');
      Data=Box.substr(0,StringPos);
      Clip.x=atoi(Data.c_str());
      
      StringPos=Box.find(';')+1;
      Box=Box.substr(StringPos);
      
      StringPos=Box.find(';');
      Data=Box.substr(0,StringPos);
      Clip.y=atoi(Data.c_str());

      StringPos=Box.find(';')+1;
      Box=Box.substr(StringPos);
      
      StringPos=Box.find(';');
      Data=Box.substr(0,StringPos).c_str();
      Clip.w=atoi(Data.c_str());

      StringPos=Box.find(';')+1;
      Box=Box.substr(StringPos);

      StringPos=Box.find(')');
      Data=Box.substr(0,StringPos);
      Clip.h=atoi(Data.c_str());
    }
  else
    {
      Clip.x=0;
      Clip.y=0;
      if (image_!=NULL)
	{
	  Clip.w=image_->w;
	  Clip.h=image_->h;
	}
      else
	{
	  Clip.w=0;
	  Clip.h=0;
	};
    };
  setDimensions(Clip.w,Clip.h);
  Position CurrentPosition=getPosition();
  applyImage(ScreenPosition.X+CurrentPosition.X,ScreenPosition.Y+CurrentPosition.Y,image_,screen,&Clip);
};
