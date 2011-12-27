#include "tbfe/UI/ImageBox.h"
ImageBox::ImageBox(int x,int y,string Source):Element(x,y)
{
  intermediary_=NULL;
  string Special=Source;
  string ImageSource=Source;
  if (ImageSource.find('(')<ImageSource.size())
    {
      ImageSource=ImageSource.substr(0,ImageSource.find('('));
    };  
  setProperty("imageSource",ImageSource);
  //TODO: setup texture generation
  image_=NULL;//TBFE_Base::CheckSheets(ImageSource.c_str());

  if (Special.find('(')<Special.length())
    {
      string Box;
      string Data;
      int StringPos;
      int w;
      int h;
      Box=Special.substr(Special.find('(')+1);
      
      StringPos=(int)Box.find(';');
      Data=Box.substr(0,StringPos);
      setProperty("clipX",Data);
      
      StringPos=Box.find(';')+1;
      Box=Box.substr(StringPos);
      
      StringPos=Box.find(';');
      Data=Box.substr(0,StringPos);
      setProperty("clipY",Data);

      StringPos=Box.find(';')+1;
      Box=Box.substr(StringPos);
      
      StringPos=Box.find(';');
      Data=Box.substr(0,StringPos).c_str();
      w=atoi(Data.c_str());

      StringPos=Box.find(';')+1;
      Box=Box.substr(StringPos);

      StringPos=Box.find(')');
      Data=Box.substr(0,StringPos);
      h=atoi(Data.c_str());
      setDimensions(w,h);
      return;
    }
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
};
void ImageBox::reload()
{
  //TODO: setup texture generation
  image_=NULL;//=TBFE_Base::CheckSheets(getProperty("imageSource").c_str());
  if (image_==NULL)
    {
      intermediary_=NULL;
      return;
    };
  SDL_Rect Clip;
  PositionI dimensions=getDimensions();
  Clip.x=0;
  Clip.y=0;
  Clip.w=dimensions.X;
  Clip.h=dimensions.Y;
  if (getProperty("clipX")!="")
    {
      Clip.x=atoi(getProperty("clipX").c_str());
    };
  if (getProperty("clipY")!="")
    {
      Clip.y=atoi(getProperty("clipY").c_str());
    };
  if (dimensions.X>image_->w || dimensions.Y>image_->h || dimensions.X<0 || dimensions.Y<0)
    {
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
      setDimensions(Clip.w,Clip.h);
    };
  PositionI CurrentPosition=getPosition();
  if (intermediary_!=NULL)
    {
      SDL_FreeSurface(intermediary_);
    };
  intermediary_=SDL_CreateRGBSurface(0,Clip.w,Clip.h,32,
				     0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  SDL_SetAlpha(image_,0,0);
  SDL_BlitSurface(image_,&Clip,intermediary_,NULL);
  setProperty("reload","1");
};
SDL_Surface * ImageBox::renderElement()
{
  reload();
  return intermediary_;
};
