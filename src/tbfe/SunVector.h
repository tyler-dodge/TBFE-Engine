#ifndef SunVector_L
#define SunVector_L
#include <math.h>
#include "actor/Actor.h"
class SunVector
{
 public:
  double CurrentPositionX;
  double CurrentPositionY;
  double Angle;
  int Speed;
  SunVector(int,int,int);
  SunVector();
  void Calculate(int);
};
#endif
