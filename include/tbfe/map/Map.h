class Map;
#ifndef Map_L
#define Map_L
#include <boost/python.hpp>
#include "tbfe/Base.h"
#include "tbfe/misc/Structs.h"
#include "tbfe/misc/Enums.h"
#include "tbfe/misc/StringConversion.h"
#include "tbfe/map/TileLayer.h"
#include <iostream>
#include <fstream>
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
  Position getDimensions();
  bool checkChanged();
  void setChanged(bool);
  void changeTile(int,int,Tile,int);
  Tile getTile(int,int,int);

  void addTileSet(string);
  string getTileSet(int);
  int getNumberOfTileSets();
};
#endif
