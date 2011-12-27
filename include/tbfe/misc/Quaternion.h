struct Quaternion;
#ifndef Quaternion_L
#define Quaternion_L
#include<math.h>
#include "tbfe/misc/Position.h"
struct Quaternion
{
public:
  float x,y,z,w;
  Quaternion();
  Quaternion(float,float,float,float);
  Matrix toMatrix();
  Quaternion operator*(Quaternion);
  void operator*=(Quaternion);
  PositionF operator*(PositionF);
  //Quaternion conj();
  void normalize();
};
#endif
