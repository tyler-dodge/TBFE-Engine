#ifndef SdlFunctions_L
#define SdlFunctions_L
class SDL_Surface;
class SDL_Rect;
#include "tbfe/misc/Enums.h"
#include "tbfe/misc/Position.h"
#include <string>
#include "tbfe/misc/Structs.h"
using namespace std;
extern SDL_Surface *loadImage(std::string filename,bool UseA=true);
extern void applyImage(int,int,SDL_Surface*,SDL_Rect*);
extern unsigned int getPixel( SDL_Surface *, int, int);
//extern void drawNodes(ModelData *, PositionF,Quaternion,PositionF);
extern GLuint bindImage(SDL_Surface*);
extern float roundDown(float,int);
extern PositionF applyRotations(PositionF,Quaternion);
extern float convertToAngle(float,float);
extern PositionF normalize(Quad);
extern float absVal(float);
extern PositionF addNormals(PositionF,PositionF);
extern PositionF crossProduct(PositionF,PositionF);
extern Quaternion getQuaternionXYZ(float,float,float);
#endif
