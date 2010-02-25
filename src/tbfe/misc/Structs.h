#ifndef Structs_L
#define Structs_L
#include <SDL/SDL_opengl.h>
#include "Enums.h"
#include <string>
#include <vector>
#include "SDL/SDL.h"
#include <aiScene.h>
using namespace std;
class Window;
class Element;

struct AnimationSheet
{
  SDL_Surface * Data;
  std::string Source;
  bool isLoaded;
};
struct Model
{
  aiScene * Data;
  std::string Source;
  bool isLoaded;
};
struct Tile
{
  TileType Type;
  int TileSet;
  int Passability;
};
struct PositionF
{
  float X;
  float Y;
  float Z;
};
struct Position
{
  int X;
  int Y;
  int Z;
};
struct PositionD
{
  double X;
  double Y;
  double Z;
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
};
struct TileSheet
{
  GLuint texture;
  Position dimensions;
};
#endif
