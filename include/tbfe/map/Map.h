class Map;
#ifndef Map_L
#define Map_L
#include "tbfe/map/TileLayer.h"
#include "tbfe/Console.h"
#include "tbfe/misc/CollidedTile.h"
#include <string>
#include <vector>
using namespace std;
class Map
{
 private:
  vector<TileLayer> layers_;
  vector<string> tileSetNames_;
  string scriptFile_;
  bool isChanged_;
 public:

  //Constructor, Creates pointer to the console
  Map();
  ~Map();

  void generateMap(int,int);
    
  bool loadMap(string);
  bool dumpMap(string);

  //Checks for collisions in map
  vector<CollidedTile> collisionTest(int,int);


  void addLayer(TileLayer);
  bool getLayerVisibility(int);
  void setLayerVisibility(int,bool);
  int getNumberOfLayers();
  PositionI getDimensions();
  bool checkChanged();
  void setChanged(bool);
  void changeTile(int,int,Tile,int);
  Tile getTile(int,int,int);

  void addTileSet(string);
  string getTileSet(int);
  int getNumberOfTileSets();
};
#endif
