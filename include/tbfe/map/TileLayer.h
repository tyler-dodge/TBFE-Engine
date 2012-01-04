#ifndef TileLayer_L
#define TileLayer_L
#include<vector>
#include "tbfe/misc/CollidedTile.h"
using namespace std;

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
class TileLayer
{
 private:
  vector<Tile> data_;
  PositionI dimensions_;
  bool isVisible_;
 public:
  TileLayer(int,int);
  TileLayer();
  void generateMap(int,int,Tile);
  PositionI getDimensions();
  Tile getTile(int,int);
  void changeTile(int,int,Tile);
  bool getVisibility();
  void setVisibility(bool);
};
#endif
