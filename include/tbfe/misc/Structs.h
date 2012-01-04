#ifndef Structs_L
#define Structs_L
class SDL_Surface;
#include <SDL/SDL_opengl.h>
#include "tbfe/misc/Enums.h"
#include <string>
#include <vector>
#include <sstream>
#include "tbfe/misc/Position.h"
#include "tbfe/misc/Matrix.h"
using namespace std;
class Window;
class Element;
struct AnimationSheet
{
  SDL_Surface * Data;
  std::string Source;
  GLuint Texture;
  bool isLoaded;
};
struct ActorType
{
  std::string Name;
  std::string Source;
  std::string Script;
  std::string Collision;
  std::string Conversation;
};
struct ElementList
{
  std::string Name;
  std::string Type;
  PositionI ElementPosition;
  std::string Special;
};
struct EventType
{
  Window * Parent;
  std::string TargetName;
  Element * TargetElement;
  Event TargetEvent;
  bool Enabled;
  std::string Function;
  int Key;
  bool keyDown;
};
struct TileSheet
{
  GLuint texture;
  PositionI dimensions;
};
struct Quad
{
  PositionF points[4];
  PositionF * at(int num)
  {
    if (num<4)
      {
	return &points[num];
      }
    else
      {
	PositionF fail(-1,-1,-1);
	return NULL;
      };
  };
};
#endif
