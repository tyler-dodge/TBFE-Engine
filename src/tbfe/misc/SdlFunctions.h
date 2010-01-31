#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../Base.h"
#include "Structs.h"
#include <string>
#include <sstream>
#ifndef SdlFunctions_L
#define SdlFunctions_L
using namespace std;
extern SDL_Surface *loadImage(std::string filename,bool UseA=true);
extern void applyImage(int,int,SDL_Surface*,SDL_Surface *,SDL_Rect * clip=NULL);
extern Uint32 getPixel( SDL_Surface *, int, int);
#endif
