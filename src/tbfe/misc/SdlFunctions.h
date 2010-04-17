#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../Base.h"
#include "Enums.h"
#include "Structs.h"
#include <string>
#include <sstream>
#include <assimp.hpp>
#include <assimp.h>
#include <aiScene.h>
#include <aiPostProcess.h>
#include "SDL/SDL_opengl.h"
#include <math.h>
#ifndef SdlFunctions_L
#define SdlFunctions_L
using namespace std;
extern SDL_Surface *loadImage(std::string filename,bool UseA=true);
extern void applyImage(int,int,SDL_Surface*,SDL_Rect*);
extern Uint32 getPixel( SDL_Surface *, int, int);
extern ModelData * loadModel(string);
extern void drawNodes(ModelData *, aiVector3D,aiVector3D,aiVector3D);
extern void applyMaterial(const struct aiMaterial *);
extern GLuint bindImage(SDL_Surface*);
extern float roundDown(float,int);
extern PositionF applyRotations(PositionF,PositionF);
extern float convertToAngle(float,float);
extern PositionF normalize(Quad,PositionF);
extern float absVal(float);
#endif
