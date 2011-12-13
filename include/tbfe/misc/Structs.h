#ifndef Structs_L
#define Structs_L
#include <boost/python.hpp>
#include <SDL/SDL_opengl.h>
#include "tbfe/misc/Enums.h"
#include <string>
#include <vector>
#include "SDL/SDL.h"
#include <sstream>
#include "tbfe/misc/PositionF.h"
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
struct MeshData
{
  vector<GLuint> indices;
  vector<GLfloat> vertices;
  vector<PositionF> texCoords;
  vector<GLfloat> normals;
  int material;
};
struct ModelData
{
  vector<int> materials;
  vector<MeshData *> meshes;
};
struct Model
{
  ModelData * Data;
  std::string Source;
  bool isLoaded;
};
struct Tile
{
  Tile(int type, int tileSet,int passability)
  {
    Type=type;
    TileSet=tileSet;
    Passability=passability;
    isChanged=false;
  };
  Tile()
  {
    Type=0;
    TileSet=0;
    Passability=0;
    isChanged=false;
  };
  int Type;
  int TileSet;
  int Passability;
  bool isChanged;
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
