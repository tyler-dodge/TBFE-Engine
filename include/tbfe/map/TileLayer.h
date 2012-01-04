#ifndef TileLayer_L
#define TileLayer_L
#include<vector>
#include"tbfe/misc/Structs.h"
using namespace std;
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
