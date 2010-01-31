#include "../misc/Structs.h"
#include "../misc/Enums.h"

#ifndef OverMap_L
#define OverMap_L
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
