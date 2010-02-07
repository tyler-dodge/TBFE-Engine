#include "SdlFunctions.h"
SDL_Surface *loadImage(std::string filename,bool UseA)
{  
  if (SDL_WasInit(SDL_INIT_VIDEO)==0)
    {
      SDL_Init(SDL_INIT_VIDEO);
    };
  SDL_Surface* original=NULL;
  SDL_Surface* newImage=NULL;
  original=IMG_Load(filename.c_str());
  if (original!=NULL)
    {
      if (UseA==true)
	{
	  newImage=SDL_DisplayFormatAlpha(original);
	}
      else
	{
	  newImage=SDL_DisplayFormat(original);
	};
      SDL_FreeSurface(original);
    };
  if (newImage==NULL)
    {
      TBFE_Base::MainConsole.write("   "+filename+" did not load correctly");
    };
  return newImage;
};
void applyImage(int x,int y,SDL_Surface* source,SDL_Surface* target, SDL_Rect* clip)
{
  SDL_Rect offset;
  offset.x=x;
  offset.y=y;
  if (clip!=NULL && source!=NULL)
    {
      if (clip->x+clip->w > source->w || clip->y+clip->h > source->h)
	{
	  return;
	};
    };
  if (source!=NULL)
    {
      SDL_BlitSurface(source, clip, target, &offset);
    };
};
Uint32 getPixel( SDL_Surface *surface, int x, int y )
{
  if (surface==NULL)
    {
      TBFE_Base::MainConsole.write("surface does not exist");
      return -1;
    };
  if (x>surface->w || y>surface->h || x<0 || y<0)
    {
      return -1;
    };
    //Convert the pixels to 32 bit
  Uint32 *pixels = (Uint32 *)surface->pixels;
    
    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}

