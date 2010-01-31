#include "Actor.h"
#include "ActorCreate.h"
#include <vector>
#include <string>
#ifndef Building_L
#define Building_L
class Building
{
 private:
  vector<Tile> floor_;
  vector<Tile> roof_;
  Position position_;
  Position floorDimensions_;
  Position roofDimensions_;
  vector<Actor *> walls_;
 public:
  Building(string,string,string,int,int);
  ~Building();
  Tile getFloorTile(int,int);
  Tile getRoofTile(int,int);

  Position getPosition();
  void setPosition(int,int);
  
  Position getFloorDimensions();
  void setFloorDimensions(int, int);
  
  Position getRoofDimensions();
  void setRoofDimensions(int,int);

  Actor * getWall(int);
  int getNumberOfWalls();
};
#endif
