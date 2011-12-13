#ifndef OverMap_L
#define OverMap_L
#include <boost/python.hpp>
#include "tbfe/misc/Structs.h"
#include "tbfe/misc/Enums.h"
using namespace std;
class OverMap
{
 private:
  Position currentPosition;
  int width;
  int height;
 public:
  string getPoint(int,int);
  string * MapLocations;
  OverMap(int,int);
  ~OverMap();
  Position GetPosition();
  void SetPosition(int, int);
  void SetPoint(int,int,std::string);
  int GetWidth();
  int GetHeight();
  string PlayerMove(Direction);
};
#endif
