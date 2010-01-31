class Map;
#ifndef Map_L
#define Map_L
#include "../Base.h"
#include "../misc/Structs.h"
#include "../misc/Enums.h"
#include "../misc/StringConversion.h"
#include "TileLayer.h"
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

  void changeTile(int,int,Tile,int);
  Tile getTile(int,int,int);

  void addTileSet(string);
  string getTileSet(int);
  int getNumberOfTileSets();
};
#endif
