#ifndef Structs_L
#define Structs_L
#include <SDL/SDL_opengl.h>
#include "Enums.h"
#include <string>
#include <vector>
#include "SDL/SDL.h"
#include <aiScene.h>
#include <sstream>
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
struct Model
{
  aiScene * Data;
  std::string Source;
  bool isLoaded;
};
struct ModelData
{
  vector<GLuint> indices;
  vector<GLfloat> vertices;
  vector<GLfloat> texCoords;
  vector<GLfloat> normals;
};
struct Tile
{
  TileType Type;
  int TileSet;
  int Passability;
  bool isChanged;
};
struct PositionF
{
  float X;
  float Y;
  float Z;
  PositionF operator+(PositionF newPosition)
  {
    newPosition.X+=X;
    newPosition.Y+=Y;
    newPosition.Z+=Z;
    return newPosition;
  };
  PositionF operator-(PositionF newPosition)
  {
    newPosition.X-=X;
    newPosition.Y-=Y;
    newPosition.Z-=Z;
    return newPosition;
  };
  void operator+=(PositionF newPosition)
  {
    X+=newPosition.X;
    Y+=newPosition.Y;
    Z+=newPosition.Z;
  };
  void operator-=(PositionF newPosition)
  {
    X-=newPosition.X;
    Y-=newPosition.Y;
    Z-=newPosition.Z;
  };
  PositionF operator/(float num)
  {
    PositionF newPosition;
    newPosition.X=X/num;
    newPosition.Y=Y/num;
    newPosition.Z=Z/num;
    return newPosition;
  };
  string dumpString()
  {
    std::stringstream text;
    text << '(' << X << ',' << Y << ',' << Z << ')';
    return text.str();
  };
};
struct Position
{
  int X;
  int Y;
  int Z;
};
struct CollidedTile
{
  int Passability;
  Position position;
};
struct Property
{
  string Name;
  string Value;
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
  Position ElementPosition;
  std::string Special;
};
struct WindowType
{
  std::string Name;
  vector<ElementList> Elements;
  int Width;
  int Height;
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
  Position dimensions;
};
#endif
