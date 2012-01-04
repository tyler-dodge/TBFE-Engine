#ifndef OverMap_L
#define OverMap_L
#include "tbfe/misc/Position.h"
using namespace std;
class OverMap
{
 private:
  PositionI currentPosition;
  int width;
  int height;
 public:
  string getPoint(int,int);
  string * MapLocations;
  OverMap(int,int);
  ~OverMap();
  PositionI GetPosition();
  void SetPosition(int, int);
  void SetPoint(int,int,std::string);
  int GetWidth();
  int GetHeight();
  string PlayerMove(Direction);
};
#endif
