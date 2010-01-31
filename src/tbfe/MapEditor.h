#include "Main.h"
class MapEditor:public TBFE
{
 private:
 public:
  bool ShowCursor;
  int CursorResistance;
  Direction EditorLoop();
  SDL_Surface * Panel;
  SDL_Surface * SelectSquare;
  SDL_Surface * Text;
  TileType NewType;
  int CurrentSet;
  bool KeysDown[311];
  Position Cursor;
  int Passability;
  int MapX;
  int MapY;
  int OffsetY;
  int StringLength;
  bool ShowCollision;
  int Layer;
  string TextInput();
  MapEditor();
  ~MapEditor();
};
