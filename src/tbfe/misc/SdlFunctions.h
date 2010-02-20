#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../Base.h"
#include "Structs.h"
#include <string>
#include <sstream>
#include <assimp.hpp>
#include <assimp.h>
#include <aiScene.h>
#include <aiPostProcess.h>
#include "SDL/SDL_opengl.h"
#ifndef SdlFunctions_L
#define SdlFunctions_L
using namespace std;
extern SDL_Surface *loadImage(std::string filename,bool UseA=true);
extern void applyImage(int,int,SDL_Surface*,SDL_Surface *,SDL_Rect * clip=NULL);
extern Uint32 getPixel( SDL_Surface *, int, int);
extern aiScene * loadModel(string);
extern void drawNodes(aiScene *,aiNode *, aiVector3D,int,aiVector3D,aiVector3D);
extern void applyMaterial(const struct aiMaterial *);
#endif
